/*****************************************************************************
**
**  Name:          btm_sec_nv.h
**
**  Description:   This file contains definition of managing link key storage inside bt stack
**
**  Copyright (c) 1999-2014, Broadcom Corp., All Rights Reserved
**  Broadcom Bluetooth Core. Proprietary and confidential.
******************************************************************************/
#pragma once

#include "btm_int.h"

/* Stored key type for KEY_ELEM_HDR */
#define BTM_STORE_KEY_TYPE_BR_EDR_LKEY      0x00ff    /* BR-EDR link key*/
#define BTM_STORE_KEY_TYPE_BLE_PENC_KEY     0x0002    /* Peer encryption Key*/
#define BTM_STORE_KEY_TYPE_BLE_PCSRK_KEY    0x0004    /* Peer SRK */
#define BTM_STORE_KEY_TYPE_BLE_LENC_KEY     0x0008    /* Master role security information: div*/
#define BTM_STORE_KEY_TYPE_BLE_LCSRK_KEY    0x0010    /* Master device ID key*/
#define BTM_STORE_KEY_TYPE_BLE_PID_KEY      0x0020    /* Peer Identity key*/


typedef struct{
    UINT16 key_type;
}tBTM_SEC_KEY_ELEM_HDR;

typedef struct{
    tBTM_SEC_KEY_ELEM_HDR  key_hdr;
    UINT8  key_data[1];  /* Maximum key length to be stored used for local variables */
}tBTM_SEC_KEY_ELEM;


/* Combined BR/EDR and BLE security keys

    For each entry is stored as below
    Key_blobs are comprised of tBTM_SEC_KEY_ELEM_HDR + RAW Key data having length as key_elem_hdr
*/
typedef struct {
    BD_ADDR    bd_addr;
    UINT16     length;
    UINT8      addr_type;
    UINT8      device_type;
    UINT8      key_blobs[1];
} tBTM_SEC_KEYS_ENTRY_T;


/*******************************************************************************
**
** Function         btm_store_link_key_blobs
**
** Description      This function converted linkkeys and store to nvram
**
** Returns          tBTM_STATUS
**
*******************************************************************************/
tBTM_STATUS btm_sec_nv_store_linkkey_blobs(tBTM_SEC_DEV_REC *p_dev_rec);





/*******************************************************************************
**
** Function         btm_restore_link_key_from_keyblobs
**
** Description      This function converted keyblobs stored in nvram to link keys
**
** Returns
**
*******************************************************************************/
tBTM_STATUS btm_sec_nv_get_linkkey_from_blobs(tBTM_SEC_DEV_REC  *p_dev_rec);



/*******************************************************************************
**
** Function         btm_sec_nv_get_key_by_keytype
**
** Description      This function converted keyblobs stored in DCT to link keys
**
** Returns
**
*******************************************************************************/
tBTM_STATUS btm_sec_nv_get_key_by_keytype(BD_ADDR bd_addr, tBTM_LE_KEY_TYPE key_type, tBTM_SEC_KEY_VALUE *p_sec_keys);


/*******************************************************************************
**
** Function         btm_sec_nv_load_pid_db
**
** Description      This function loads PID keys from nvram to ram
**
** Returns
**
********************************************************************************/
void btm_sec_nv_load_pid_db(void);


/*******************************************************************************
**
** Function         btm_sec_nv_refresh_rpa
**
** Description      This function loads update bd_addr key with new resolvable random address
**
** Returns
**
********************************************************************************/
void btm_sec_nv_refresh_rpa(BD_ADDR bd_addr, BD_ADDR refresh_rpa);


