/*****************************************************************************
**                                                                           *
**  Name:          wiced_post_reset.c                                        *
**                                                                           *
**  Description:   Post controller reset routines                            *
**                                                                           *
**  Copyright (c) 2013, Broadcom Corp., All Rights Reserved.                 *
******************************************************************************/
#include "bt_target.h"
#include "userial.h"
#include "btu.h"
#include "brcm_api.h"
#include "btm_api.h"
#include "btm_int.h"

/******************************************************
 *                    Constants
 ******************************************************/
#define BTE_MAIN_HCI_RECONFIG_BAUD          TRUE
#define BTE_MAIN_HCI_RECONFIG_BAUD_RATE     USERIAL_BAUD_1M
#define BTE_MAIN_HCI_RECONFIG_CLOCK_RATE    48000000

/* Patchram definitions */
//extern const UINT8 brcm_patchram_format;
//extern const UINT8 brcm_patchram_buf[];
//extern const int brcm_patch_ram_length;
UINT32 get_hcd_content_length();
extern void platform_USART_Config(uint32_t baud);

/* BTE host stack initialization callback */
void bte_post_stack_init_cback(UINT8 status)
{
    tBTM_EVENT_DATA event_data;

    if (status == BTM_SUCCESS)
    {
        /* Enable BTM BLE scatternet */
        BTM_BleScatternetEnable(TRUE);
    }

    /* Notify the app that host stack has been initialized */
    event_data.enabled.status = status;
    (*btm_cb.p_management_callback)(BTM_ENABLED_EVT, &event_data);
}

void bte_post_download_baud_update_cback(UINT8 status)
{
#if (defined(HCILP_INCLUDED) && HCILP_INCLUDED == TRUE)
    HCILP_Enable(NULL, NULL);
#endif
}

void bte_prm_cback(tBRCM_PRM_STATUS status)
{
    if (status ==BRCM_PRM_STS_COMPLETE)
    {
        APPL_TRACE_ERROR0("Patch successfully downloaded. Proceding with startup...");
#if (defined(BTE_MAIN_HCI_RECONFIG_BAUD) && (BTE_MAIN_HCI_RECONFIG_BAUD == TRUE))
        
        platform_USART_Config(USERIAL_GetLineSpeed(USERIAL_BAUD_115200));
        GKI_delay(100);
        HCIUTIL_UpdateBaudRate(BTE_MAIN_HCI_RECONFIG_BAUD_RATE,
            BTE_MAIN_HCI_RECONFIG_CLOCK_RATE,
            bte_post_download_baud_update_cback);
#endif        
        BTM_ContinueReset();
    }
    else
    {
        APPL_TRACE_ERROR1("bte_prm_cback failed status=0x%x", status);
    }
}

void bte_baud_update_cback(UINT8 status)
{
    APPL_TRACE_DEBUG1("bte_baud_update_cback status=%i", status);

    /* Delay for 50ms to allow controller to set new baud rate */
    GKI_delay(150);

    //BRCM_PrmInit (bte_prm_cback, (UINT8 *)brcm_patchram_buf, brcm_patch_ram_length, 0, brcm_patchram_format);
    BRCM_PrmInit(bte_prm_cback, 0, get_hcd_content_length(), 0, BTE_PRM_FORMAT_HCD);
}

void bte_post_reset(void)
{
    APPL_TRACE_DEBUG0("bte_post_reset");

    BTM_RegisterForDeviceStatusNotif (bte_post_stack_init_cback);

#if (defined(BTE_MAIN_HCI_RECONFIG_BAUD) && (BTE_MAIN_HCI_RECONFIG_BAUD == TRUE))
    HCIUTIL_UpdateBaudRate(BTE_MAIN_HCI_RECONFIG_BAUD_RATE,
            BTE_MAIN_HCI_RECONFIG_CLOCK_RATE,
            bte_baud_update_cback);
#else
    bte_baud_update_cback(HCIUTIL_STATUS_SUCCESS);
#endif
}
