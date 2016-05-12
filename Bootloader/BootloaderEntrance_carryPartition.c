/**
******************************************************************************
* @file    BootloaderEntrance.c 
* @author  William Xu
* @version V2.0.0
* @date    05-Oct-2014
* @brief   MICO bootloader main entrance.
******************************************************************************
*
*  The MIT License
*  Copyright (c) 2014 MXCHIP Inc.
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy 
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights 
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is furnished
*  to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in
*  all copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
*  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR 
*  IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
******************************************************************************
*/ 


#include "Mico.h"
#include "MicoPlatform.h"
#include "platform.h"
#include "platformInternal.h"
#include "platform_config.h"
#include "bootloader.h"
#include "CheckSumUtils.h"

#define boot_log(M, ...) custom_log("BOOT", M, ##__VA_ARGS__)
#define boot_log_trace() custom_log_trace("BOOT")

extern void Main_Menu(void);
extern OSStatus update(void);

#ifdef SIZE_OPTIMIZE
char menu[] =
"\r\n"
"MICO bootloader for %s, %s, HARDWARE_REVISION: %s\r\n"
"0:BOOTUPDATE,"
"1:FWUPDATE,"
"2:DRIVERUPDAT,"
"3:PARAUPDATE,"
"4:FLASHUPDATE,"
"5:MEMORYMAP,"
"6:BOOT,"
"7:REBOOT";
#ifdef MICO_USE_BT_PARTITION
"8:BT DRIVERUPDAT,"
#endif
#else
char menu[] =
"\r\n"
"MICO bootloader for %s, %s, HARDWARE_REVISION: %s\r\n"
"+ command -------------------------+ function ------------+\r\n"
"| 0:BOOTUPDATE    <-r>             | Update bootloader    |\r\n"
"| 1:FWUPDATE      <-r>             | Update application   |\r\n"
"| 2:DRIVERUPDATE  <-r>             | Update RF driver     |\r\n"
"| 3:PARAUPDATE    <-r><-e>         | Update MICO settings |\r\n"
"| 4:FLASHUPDATE   <-dev device>    |                      |\r\n"
"|  <-e><-r><-start addr><-end addr>| Update flash content |\r\n"
"| 5:MEMORYMAP                      | List flash memory map|\r\n"
"| 6:BOOT                           | Excute application   |\r\n"
"| 7:REBOOT                         | Reboot               |\r\n"
#ifdef MICO_USE_BT_PARTITION
"| 8:BT DRIVERUPDATE  <-r>           | Update BT driver     |\r\n"
#endif
"+----------------------------------+----------------------+\r\n"
"|    (C) COPYRIGHT 2015 MXCHIP Corporation  By William Xu |\r\n"
" Notes:\r\n"
" -e Erase only  -r Read from flash -dev flash device number\r\n"
"  -start flash start address -end flash start address\r\n"
" Example: Input \"4 -dev 0 -start 0x400 -end 0x800\": Update \r\n"
"          flash device 0 from 0x400 to 0x800\r\n";
#endif

#ifdef MICO_ENABLE_STDIO_TO_BOOT
extern int stdio_break_in(void);
#endif

static void enable_protection( void )
{
  mico_partition_t i;
  mico_logic_partition_t *partition;

  for( i = MICO_PARTITION_BOOTLOADER; i < MICO_PARTITION_MAX; i++ ){
    partition = MicoFlashGetInfo( i );
    if( PAR_OPT_WRITE_DIS == ( partition->partition_options & PAR_OPT_WRITE_MASK )  )
      MicoFlashEnableSecurity( i, 0x0, MicoFlashGetInfo(i)->partition_length );
  }
}

WEAK bool MicoShouldEnterBootloader( void )
{
  return false;
}

WEAK bool MicoShouldEnterMFGMode( void )
{
  return false;
}

WEAK bool MicoShouldEnterATEMode( void )
{
  return false;
}

//add by Zhaozh for carry partition for spi flash, start
#define SizePerRW 4096   /* Bootloader need 2xSizePerRW RAM heap size to operate,
                            but it can boost the setup. */

static uint8_t data[SizePerRW];
static OSStatus checkcrc_for_partition(uint16_t crc_in, int partition_type, int total_len)
{
  uint16_t crc = 0;
  mico_logic_partition_t* part;
  int len;
  OSStatus err = kUnknownErr;
  uint32_t update_data_offset = 0x0;
  CRC16_Context contex;

  CRC16_Init( &contex );

  if (crc_in == 0xFFFF)
    goto exit;

  part = MicoFlashGetInfo((mico_partition_t)partition_type);
  if (part == NULL)
    goto exit;

  while(total_len > 0){
    if( SizePerRW < total_len ){
      len = SizePerRW;
    } else {
      len = total_len;
    }
    err = MicoFlashRead( (mico_partition_t)partition_type, &update_data_offset, data , len);
    require_noerr(err, exit);

    total_len -= len;

    CRC16_Update( &contex, data, len );
  }

  CRC16_Final( &contex, &crc );
  if (crc == crc_in){
    err = kNoErr;
  }
  else{
    err = kChecksumErr;
  }

exit:
  if(kNoErr != err){
    printf("   CRC check return %d, got crc %x, calcuated crc %x\r\n", err, crc_in, crc);
  }
  return err;
}

static uint16_t checkBinCrc(uint32_t startaddr, int binlen)
{
  uint16_t crc = 0;
  uint8_t * pdata = (uint8_t *)startaddr;
  CRC16_Context contex;
  CRC16_Init( &contex );
  CRC16_Update( &contex, pdata, binlen );
  CRC16_Final( &contex, &crc );
  crc = contex.crc;
  return crc;
}

typedef struct
{
    uint16_t headflag; //0x7e7e
    uint16_t count;//how many partition need to carry.
}PART_HEAD;

typedef struct
{
    uint16_t padTableItemflag;//0x7e7e
    uint16_t partition_type;
    uint32_t startaddres;//at bin, not flash, add flash offset to use it
    uint32_t length;//data length
    uint16_t crc;
    uint16_t next;//true 0x7e7e,false not 0x7e7e
    uint32_t carriedFlag;//false 0xffffffff
}PARTITION_TABLEITEM;

char part_type_str[MICO_PARTITION_MAX][20] ={
"0:Bootloader",
"1:Application",
"2:ATE",
"3:OTA TEMP",
"4:RF",
"5:Parameter 1",
"6:Parameter 2",
"7:Bluetooth",
};
extern const mico_logic_partition_t mico_partitions[] ;
void copy_driver_to_spi_flash( void )
{
  OSStatus err = kUnknownErr;
  mico_logic_partition_t *partion_info = NULL;
  uint32_t src_startaddr=0;
  uint32_t offset = 0x00;
  uint32_t bin_size = 0x0;
  uint16_t bin_crc16 = 0x0;
  uint32_t WrCount = 0;
  uint32_t copyLength = 0;
  uint32_t dest_offset = 0;
  uint16_t current_crc16 = 0;
  uint32_t carry_flag = 0;
  int i=0;
  CRC16_Context contex;
  uint32_t onchipflash_addr;
   uint32_t app_start_addr;

  MicoSysLed(false);

  partion_info = MicoFlashGetInfo(MICO_PARTITION_BOOTLOADER);
  require_action( (NULL != partion_info) && (partion_info->partition_owner != MICO_FLASH_NONE),
                 exit, err = kUnsupportedErr );
  onchipflash_addr = partion_info->partition_start_addr;

  partion_info = MicoFlashGetInfo(MICO_PARTITION_APPLICATION);
  require_action( (NULL != partion_info) && (partion_info->partition_owner != MICO_FLASH_NONE),
                 exit, err = kUnsupportedErr );
  app_start_addr = partion_info->partition_start_addr;

  //get partiton table info
  PART_HEAD part_head;
  PARTITION_TABLEITEM part_tableitem[MICO_PARTITION_MAX];
  memcpy(&part_head, (uint8_t *)app_start_addr,4);
  require_action( (part_head.headflag == 0x7e7e),exit, err = kUnknownErr );
  if((part_head.count >0)&&(part_head.count <MICO_PARTITION_MAX))
  {
    memcpy(&part_tableitem, ((uint8_t *)app_start_addr)+4,20*(part_head.count));
  }

  if((part_head.count >0)&&(part_head.count <MICO_PARTITION_MAX))
  {
      printf("\r\nEnter Carry partition.\r\n");
      for(int itemx =0;itemx<part_head.count;itemx++)
      {
          uint16_t part_sn = part_tableitem[itemx].partition_type;
          mico_partition_t part_type = (mico_partition_t)(part_tableitem[itemx].partition_type);
          uint32_t partbin_start_addr = part_tableitem[itemx].startaddres + onchipflash_addr;
          uint32_t partbin_length = part_tableitem[itemx].length;

          if(part_tableitem[itemx].padTableItemflag !=0x7e7e)
          {
              printf("The carry table is error, exit.\r\n");
              //continue;
              goto exit;
          }
          if((part_type>=MICO_PARTITION_MAX)||(part_type<0))
          {
              printf("The partition %d type is error, exit.\r\n",part_type);
              //continue;
              goto exit;
          }
          if(part_tableitem[itemx].carriedFlag !=0xFFFFFFFF)
          {
              printf("===>The %s is already copied to spi flash.\r\n",part_type_str[part_sn]);
              continue;
          }
          if(mico_partitions[part_type].partition_owner!=MICO_FLASH_SPI)
          {
              printf("The %s partition is not in spi flash.\r\n",part_type_str[part_type]);
              continue;
          }

          //check bin crc
          uint16_t crc = checkBinCrc(partbin_start_addr,partbin_length);
          if(crc != part_tableitem[itemx].crc)
          {
                printf("%s bin CRC check error .\r\n",part_type_str[part_type]);
                //continue;
                goto exit;
          }

          partion_info = MicoFlashGetInfo(part_type);
          require_action( (NULL != partion_info) && (partion_info->partition_owner != MICO_FLASH_NONE),
                         exit, err = kUnsupportedErr );


          if(partbin_length>partion_info->partition_length)
          {
               printf("%s bin size error",part_type_str[part_type]);
               //continue;
               goto exit;
          }
           // get write permission for the partion
          err = MicoFlashDisableSecurity(part_type, 0x0, partion_info->partition_length );
          require_noerr(err, exit);

          // erase the partion
          printf("Erase %s partion...\r\n",part_type_str[part_type] );
          err = MicoFlashErase(part_type, 0x0, partion_info->partition_length );
          require_noerr(err, exit);
          printf("Erase %s partion success\r\n",part_type_str[part_type] );

          bin_size = partbin_length;
          src_startaddr = partbin_start_addr;
          dest_offset = 0;

          printf("Start to copy  %s...\r\n",part_type_str[part_type]);
          printf("copy_size = %d\r\n", bin_size);

          WrCount = (bin_size)/SizePerRW;
          CRC16_Init( &contex );
          for(offset = 0, i = 0; i <= WrCount; i++){
            if( i == WrCount ){
              if( (bin_size)%SizePerRW )
                copyLength = (bin_size)%SizePerRW;
              else
                break;
            }else{
              copyLength = SizePerRW;
            }

            memcpy(data,((uint8_t *)src_startaddr)+offset,copyLength);

            err = MicoFlashWrite( part_type, &dest_offset, data, copyLength);

            require_noerr(err, exit);
            CRC16_Update( &contex, data, copyLength );
            printf(".");
            offset+=copyLength;
          }
          printf(".\r\n");
          CRC16_Final( &contex, &current_crc16 );
          printf("current bin crc16 = 0x%2x\r\n", current_crc16);

          bin_crc16 = part_tableitem[itemx].crc;

          if(kNoErr !=  checkcrc_for_partition(bin_crc16, part_type, bin_size)){
            printf("%s partion write error\r\n" ,part_type_str[part_type]);
            err = kChecksumErr;
            goto exit;
          }
          else{
            printf("write %s partion success\r\n",part_type_str[part_type]);
          }

          // set carried flag
          offset = 4+itemx*20+16;
          carry_flag = 0;
          err = MicoFlashWrite(MICO_PARTITION_APPLICATION, &offset, (uint8_t*)&carry_flag , 4);
          require_noerr(err, exit);

          if(part_tableitem[itemx].next !=0x7e7e)
              break;
      }

  }

  printf( "===>Copy all partition success!\r\nNow you can download && run your own application!\r\n");

exit_done:
  MicoSysLed(true);

  while(1){
    //mico_thread_msleep(MICO_WAIT_FOREVER);
  }

exit:
  MicoSysLed(false);
  printf("***ERROR: Update RF driver failed, err=%d, please restart && try again!\r\n", err);
  mico_thread_msleep( MICO_WAIT_FOREVER );
}

void bootloader_start_app( uint32_t app_addr )
{
  enable_protection( );
  //startApplication( app_addr );
  copy_driver_to_spi_flash();
}


int main(void)
{
  mico_logic_partition_t *partition;
  
  init_clocks();
  init_memory();
  init_architecture();
  init_platform_bootloader();

  mico_set_bootload_ver();
  
  update();

  enable_protection();

#ifdef MICO_ENABLE_STDIO_TO_BOOT
  if (stdio_break_in() == 1)
    goto BOOT;
#endif
  
  if( MicoShouldEnterBootloader() == false )
    bootloader_start_app( (MicoFlashGetInfo(MICO_PARTITION_APPLICATION))->partition_start_addr );
  else if( MicoShouldEnterMFGMode() == true )
    bootloader_start_app( (MicoFlashGetInfo(MICO_PARTITION_APPLICATION))->partition_start_addr );
  else if( MicoShouldEnterATEMode() ){
    partition = MicoFlashGetInfo( MICO_PARTITION_ATE );
    if (partition->partition_owner != MICO_FLASH_NONE) {
      bootloader_start_app( partition->partition_start_addr );
    }
  }

BOOT:
  printf ( menu, MODEL, Bootloader_REVISION, HARDWARE_REVISION );

  while(1){                             
    Main_Menu ();
  }
}


