/*****************************************************************************
**                                                                           *
**  Name:          wiced_bt_stack.h                                          *
**                                                                           *
**  Description:   Wiced interface to bt_stack library                       *
**                                                                           *
**  Copyright (c) 2013, Broadcom Corp., All Rights Reserved.                 *
******************************************************************************/
#ifndef WICED_BT_STACK_H
#define WICED_BT_STACK_H

#include "bt_target.h"
#include "gki.h"


/*****************************************************************************
** Definitions for tWICED_BT_AUDIO_CBACK callback
*****************************************************************************/
/* Events for tWICED_BT_AUDIO_CBACK */
typedef enum {
    WICED_BT_AUDIO_EVT_CONFIG,              /* Player configuration                 */
    WICED_BT_AUDIO_EVT_GET_BUF,             /* Request buffer for audio data        */
    WICED_BT_AUDIO_EVT_GET_PLAYER_STATS,    /* Request for player statistics        */
    WICED_BT_AUDIO_EVT_DATA,                /* Data to play                         */
} tWICED_BT_AUDIO_EVT;

/* Event data structure for WICED_BT_AUDIO_EVT_GET_PLAYER_STATS */
typedef struct {
    UINT32 curr_queue_count;                /* Number of unplayed buffers in the queue */
    UINT32 player_overrun_count;            /* Number of times player had nothing to play */
} tWICED_BT_GET_PLAYER_PLAYER_STATS;

/* Union of event data structures for tWICED_BT_AUDIO_CBACK */
typedef union {
    void *p_audio_data;                             /* WICED_BT_AUDIO_EVT_DATA */
    tWICED_BT_GET_PLAYER_PLAYER_STATS player_stats; /* WICED_BT_AUDIO_EVT_GET_PLAYER_STATS */
} tWICED_BT_AUDIO_EVT_DATA;

typedef void tWICED_BT_AUDIO_CBACK(tWICED_BT_AUDIO_EVT event, tWICED_BT_AUDIO_EVT_DATA *p_evt_data);

/*****************************************************************************
** Globals
*****************************************************************************/
extern UINT8 wiced_log_enabled;

/*****************************************************************************
** Logging macro
*****************************************************************************/
extern wiced_mutex_t global_trace_mutex;
#define WPRINT_BT_APP_INFO(info)    { \
                                        wiced_rtos_lock_mutex(&global_trace_mutex);     \
                                        WPRINT_APP_INFO(info);                          \
                                        wiced_rtos_unlock_mutex(&global_trace_mutex);   \
                                    }

/*****************************************************************************
** wiced_bt_stack APIs
*****************************************************************************/
wiced_result_t wiced_bt_register_audio_cback(tWICED_BT_AUDIO_CBACK *p_audio_cback);

#endif /* WICED_BT_STACK_H */
