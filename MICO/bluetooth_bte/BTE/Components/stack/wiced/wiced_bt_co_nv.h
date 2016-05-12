/*****************************************************************************
**
**  Name:          wiced_bt_co_nv.h
**
**  Description:   Internal definitions wiced bt nv storage call out functions
**
**
**  Copyright (c) 2014, Broadcom Corp, All Rights Reserved.
**  Broadcom Bluetooth Core. Proprietary and confidential.
******************************************************************************/
#pragma once

#if defined(BTM_INTERNAL_LINKKEY_STORAGE_INCLUDED) && (BTM_INTERNAL_LINKKEY_STORAGE_INCLUDED == TRUE)


/**
 * Function     wiced_bt_callout_nv_init_cb
 *
 * initialize nvram control block
 *
 * @param[in]  max_num_bonded_devices : maximum limit of number of bonded devices
 *
 * @return  void
 */
void wiced_bt_callout_nv_init_cb(void);

/**
 * Function     wiced_bt_callout_nv_get_bonded_devices
 *
 * get lists of bonded devices stored in nvram
 *
 * @param[in]  paired_device_list : array for getting bd address of bonded devices
 * @param[in/out] p_num_devices :  list size of paired_device_list/total number of bonded devices stored
 *
 * @return      WICED_SUCCESS or ERROR
 */
tBTM_STATUS wiced_bt_callout_nv_get_bonded_devices(wiced_bt_dev_bonded_device_info_t paired_device_list[], uint16_t *p_num_devices);

/**
 * Function     wiced_bt_callout_nv_save_bonded_device_key
 *
 *  save link key information of bonded device
 *
 * @param[in]  bd_addr : bd_addr of bonded device
 * @param[in]  p_keyblobs : key blobs including key header, link keys and key length
 * @param[in]  key_len :  total length of p_keyblobs
 *
 * @return      WICED_SUCCESS or ERROR
 */
tBTM_STATUS wiced_bt_callout_nv_save_bonded_device_key(wiced_bt_device_address_t bd_addr, wiced_bt_ble_address_type_t addr_type, uint8_t device_type, uint8_t *p_keyblobs, uint16_t key_len);

/**
 * Function     wiced_bt_callout_nv_load_linkkeys
 *
 *  loads stored key information for bonded device having @bd_addr
 *
 * @param[in]  bd_addr : bd_addr of bonded device
 * @param[out]  p_key_entry :  key information stored
 *
 * @return      WICED_SUCCESS or ERROR
 */
tBTM_STATUS wiced_bt_callout_nv_load_bonded_device_keys(wiced_bt_device_address_t bd_addr, tBTM_SEC_KEYS_ENTRY_T *p_key_entry);


/**
 * Function     wiced_bt_callout_nv_delete_bonded_device
 *
 * remove key information from storage by releasing bonding with remote device having @bd_addr
 *
 * @param[in]  bd_addr : bd_addr of bonded device to be removed

 * @return      WICED_SUCCESS or ERROR
 */
tBTM_STATUS wiced_bt_callout_nv_delete_bonded_device(wiced_bt_device_address_t bd_addr);


/**
 * Function     wiced_bt_callout_nv_load_local_identity_keys
 *
 * load local identity keys including ir/irk/dhk stored in nvram
 *
 * @param[out]  p_lkeys: local identity key information
 *
 * @return      WICED_SUCCESS or ERROR
 */
tBTM_STATUS wiced_bt_callout_nv_load_local_identity_keys(tBTM_LOCAL_IDENTITY_KEY_DATA *p_lkeys);

/**
 * Function     wiced_bt_callout_nv_save_local_identity_keys
 *
 * save local identity keys including ir/irk/dhk to nvram
 *
 * @param[in]  p_lkeys : local identity key information
 *
 * @return      WICED_SUCCESS or ERROR
 */
tBTM_STATUS wiced_bt_callout_nv_save_local_identity_keys(tBTM_LOCAL_IDENTITY_KEY_DATA *p_lkeys);


/**
 * Function     wiced_bt_callout_nv_key_storage_available
 *
 * query if there are available spaces for storing key information
 * for device with @bd_addr with requested @req_size
 *
 * @param[in]  bd_addr : bd_addr of bonded device
 * @param[in]  req_size : requested size to be stored
 *
 * @return      TRUE if there is available space or FALSE
 */
BOOLEAN wiced_bt_callout_nv_key_storage_available(wiced_bt_device_address_t bd_addr,int req_size);


/**
 * Function     wiced_bt_callout_nv_enum_bonded_device_keys
 *
 *   load stored key information by enumeration
 *
 * @param[out]  p_index : index of stored key
 * @param[out]  p_key_entry : key information stored
 *
 * @return      WICED_SUCCESS or ERROR
 */
tBTM_STATUS wiced_bt_callout_nv_enum_bonded_device_keys(int8_t *p_index, tBTM_SEC_KEYS_ENTRY_T * p_key_entry);

/**
 * Function     wiced_bt_callout_nv_change_addr_key
 *
 *  save link key information of bonded device
 *
 * @param[in]  bd_addr : bd_addr of bonded device
 * @param[in]  new_bd_addr : bd addr of bonded device to be changed
 *
 * @return      WICED_SUCCESS or ERROR
 */
tBTM_STATUS wiced_bt_callout_nv_change_addr_key(wiced_bt_device_address_t bd_addr, wiced_bt_device_address_t new_bd_addr);

#endif  /*#if defined(BTM_INTERNAL_LINKKEY_STORAGE_INCLUDED) && (BTM_INTERNAL_LINKKEY_STORAGE_INCLUDED == TRUE)*/



