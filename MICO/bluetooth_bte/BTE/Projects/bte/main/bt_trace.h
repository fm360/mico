/****************************************************************************/
/*                                                                          */
/*  Name:       bt_trace.h                                                  */
/*                                                                          */
/*  Function    this file contains definitions for implementing the         */
/*              diagnostic trace message service.                           */
/*                                                                          */
/*                                                                          */
/*  Copyright (c) 1999-2014, Broadcom Corp., All Rights Reserved.           */
/*  Broadcom Bluetooth Core. Proprietary and confidential.                  */
/*                                                                          */
/****************************************************************************/
#ifndef BT_TRACE_H
#define BT_TRACE_H

#include "data_types.h"
#include "debug.h"

#ifndef BTTRC_INCLUDED
#define BTTRC_INCLUDED  FALSE
#endif
#ifndef BTTRC_PARSER_INCLUDED
#define BTTRC_PARSER_INCLUDED FALSE
#endif
#ifndef MAX_TRACE_RAM_SIZE
#define MAX_TRACE_RAM_SIZE 10000
#endif

/* BTE tracing IDs for debug purposes */
/* LayerIDs for stack */
#define BTTRC_ID_STK_GKI                   1
#define BTTRC_ID_STK_BTU                   2
#define BTTRC_ID_STK_HCI                   3
#define BTTRC_ID_STK_L2CAP                 4
#define BTTRC_ID_STK_RFCM_MX               5
#define BTTRC_ID_STK_RFCM_PRT              6
#define BTTRC_ID_STK_OBEX_C                7
#define BTTRC_ID_STK_OBEX_S                8
#define BTTRC_ID_STK_AVCT                  9
#define BTTRC_ID_STK_AVDT                  10
#define BTTRC_ID_STK_AVRC                  11
#define BTTRC_ID_STK_BIC                   12
#define BTTRC_ID_STK_BIS                   13
#define BTTRC_ID_STK_BNEP                  14
#define BTTRC_ID_STK_BPP                   15
#define BTTRC_ID_STK_BTM_ACL               16
#define BTTRC_ID_STK_BTM_PM                17
#define BTTRC_ID_STK_BTM_DEV_CTRL          18
#define BTTRC_ID_STK_BTM_SVC_DSC           19
#define BTTRC_ID_STK_BTM_INQ               20
#define BTTRC_ID_STK_BTM_SCO               21
#define BTTRC_ID_STK_BTM_SEC               22
#define BTTRC_ID_STK_DUN                   23
#define BTTRC_ID_STK_HID                   24
#define BTTRC_ID_STK_HSP2                  25
#define BTTRC_ID_STK_FTC                   26
#define BTTRC_ID_STK_FTS                   27
#define BTTRC_ID_STK_GAP                   28
#define BTTRC_ID_STK_GOEP                  29
#define BTTRC_ID_STK_OPC                   30
#define BTTRC_ID_STK_OPS                   31
#define BTTRC_ID_STK_PAN                   32
#define BTTRC_ID_STK_SAP                   33
#define BTTRC_ID_STK_SDP                   34
#define BTTRC_ID_STK_SLIP                  35
#define BTTRC_ID_STK_SPP                   36
#define BTTRC_ID_STK_VDP                   37
#define BTTRC_ID_STK_MCAP                  38
#define BTTRC_ID_STK_GATT                  39
#define BTTRC_ID_STK_SMP                   40
#define BTTRC_ID_STK_NFC                   41
#define BTTRC_ID_STK_NCI                   42
#define BTTRC_ID_STK_IDEP                  43
#define BTTRC_ID_STK_NDEP                  44
#define BTTRC_ID_STK_LLCP                  45
#define BTTRC_ID_STK_RW                    46
#define BTTRC_ID_STK_CE                    47
#define BTTRC_ID_STK_SNEP                  48
#define BTTRC_ID_STK_NDEF                  49


/* LayerIDs for BTA */
#define BTTRC_ID_BTA_ACC                   50         /* Advanced Camera Client */
#define BTTRC_ID_BTA_AG                    51         /* audio gateway */
#define BTTRC_ID_BTA_AV                    52         /* Advanced audio */
#define BTTRC_ID_BTA_BIC                   53         /* Basic Imaging Client */
#define BTTRC_ID_BTA_BIS                   54         /* Basic Imaging Server */
#define BTTRC_ID_BTA_BP                    55         /* Basic Printing Client */
#define BTTRC_ID_BTA_DG                    56         /* data gateway */
#define BTTRC_ID_BTA_DM                    57         /* device manager */
#define BTTRC_ID_BTA_DM_SRCH               58         /* device manager search */
#define BTTRC_ID_BTA_DM_SEC                59         /* device manager security */
#define BTTRC_ID_BTA_FM                    60
#define BTTRC_ID_BTA_FTC                   61         /* file transfer client */
#define BTTRC_ID_BTA_FTS                   62         /* file transfer server */
#define BTTRC_ID_BTA_HIDH                  63
#define BTTRC_ID_BTA_HIDD                  64
#define BTTRC_ID_BTA_JV                    65
#define BTTRC_ID_BTA_OPC                   66         /* object push client */
#define BTTRC_ID_BTA_OPS                   67         /* object push server */
#define BTTRC_ID_BTA_PAN                   68         /* Personal Area Networking */
#define BTTRC_ID_BTA_PR                    69         /* Printer client */
#define BTTRC_ID_BTA_SC                    70         /* SIM Card Access server */
#define BTTRC_ID_BTA_SS                    71         /* synchronization server */
#define BTTRC_ID_BTA_SYS                   72         /* system manager */
#define BTTRC_ID_AVDT_SCB                  73         /* avdt scb */
#define BTTRC_ID_AVDT_CCB                  74         /* avdt ccb */

/* LayerIDs for BT APP */
#define BTTRC_ID_BTAPP                     75
#define BTTRC_ID_MAX_ID                    BTTRC_ID_BTAPP
#define BTTRC_ID_ALL_LAYERS                0xFF       /* all trace layers */
typedef UINT8 tBTTRC_LAYER_ID;

/* Trace type definitions. Note that these are mutually exclusive in a trace. This
means that any trace can be either error,warning,api,event or dbg */
#if (BTU_STACK_LITE_ENABLED == TRUE)
#define BTTRC_TYPE_ERROR                   0x81
#define BTTRC_TYPE_WARNING                 0x82
#define BTTRC_TYPE_API                     0x84
#define BTTRC_TYPE_EVENT                   0x88
#define BTTRC_TYPE_ACTION                  0x90
#define BTTRC_TYPE_DBG                     0xA0
#else
#define BTTRC_TYPE_ERROR                   0x01       /* Traces for error situation */
#define BTTRC_TYPE_WARNING                 0x02       /* Traces for warning situation */
#define BTTRC_TYPE_API                     0x04       /* Traces for API */
#define BTTRC_TYPE_EVENT                   0x08       /* Traces for EVENT */
#define BTTRC_TYPE_ACTION                  0x10       /* Traces for Action functions */
#define BTTRC_TYPE_DBG                     0x20       /* Traces for debugging purpose */
#endif
typedef UINT8 tBTTRC_TYPE;

/* Masks to identify the stack that originated the trace */
#define BTTRC_TRACE_LITE                   0x80       /* MM Lite stack */
#define BTTRC_TRACE_EMBD                   0x40       /* Embedded host stack */

/* Parameter datatypes used in Trace APIs */
#define BTTRC_PARAM_UINT8                  1
#define BTTRC_PARAM_UINT16                 2
#define BTTRC_PARAM_UINT32                 3
typedef UINT8 tBTTRC_PARAM_TYPE;

/* Special token definitions */
#define BTTRC_TOKEN_SM_STATE               0xFFFF     /* Token indicating the State of a State m/c */


#ifdef __cplusplus
extern "C" {
#endif

/* External declaration for appl_trace_level here to avoid to add the declaration in all the files using APPL_TRACExxx macros */
extern UINT8 appl_trace_level ;

/* Prototype for message logging function. */
EXPORT_API extern void LogMsg (UINT32 trace_set_mask, const char *fmt_str, ...);
extern void LogMsg_0 (UINT32 trace_set_mask, const char *p_str);
extern void LogMsg_1 (UINT32 trace_set_mask, const char *fmt_str, UINTPTR p1);
extern void LogMsg_2 (UINT32 trace_set_mask, const char *fmt_str, UINTPTR p1, UINTPTR p2);
extern void LogMsg_3 (UINT32 trace_set_mask, const char *fmt_str, UINTPTR p1, UINTPTR p2,
                      UINTPTR p3);
extern void LogMsg_4 (UINT32 trace_set_mask, const char *fmt_str, UINTPTR p1, UINTPTR p2,
                      UINTPTR p3, UINTPTR p4);
extern void LogMsg_5 (UINT32 trace_set_mask, const char *fmt_str, UINTPTR p1, UINTPTR p2,
                      UINTPTR p3, UINTPTR p4, UINTPTR p5);
extern void LogMsg_6 (UINT32 trace_set_mask, const char *fmt_str, UINTPTR p1, UINTPTR p2,
                      UINTPTR p3, UINTPTR p4, UINTPTR p5, UINTPTR p6);

/* Prototype for stack tracing function. */
EXPORT_API extern void BTTRC_StackTrace0(tBTTRC_LAYER_ID layer_id,
                                   tBTTRC_TYPE type,
                                   UINT16 token);
EXPORT_API extern void BTTRC_StackTrace1(tBTTRC_LAYER_ID layer_id,
                                   tBTTRC_TYPE type,
                                   UINT16 token,
                                   tBTTRC_PARAM_TYPE p1_type, UINTPTR p1_val);
EXPORT_API extern void BTTRC_StackTrace2(tBTTRC_LAYER_ID layer_id,
                                   tBTTRC_TYPE type,
                                   UINT16 token,
                                   tBTTRC_PARAM_TYPE p1_type, UINTPTR p1_val,
                                   tBTTRC_PARAM_TYPE p2_type, UINTPTR p2_val);
EXPORT_API extern void BTTRC_StackTrace3(tBTTRC_LAYER_ID layer_id,
                                   tBTTRC_TYPE type,
                                   UINT16 token,
                                   tBTTRC_PARAM_TYPE p1_type, UINTPTR p1_val,
                                   tBTTRC_PARAM_TYPE p2_type, UINTPTR p2_val,
                                   tBTTRC_PARAM_TYPE p3_type, UINTPTR p3_val);
EXPORT_API extern void BTTRC_StackTrace4(tBTTRC_LAYER_ID layer_id,
                                   tBTTRC_TYPE type,
                                   UINT16 token,
                                   tBTTRC_PARAM_TYPE p1_type, UINTPTR p1_val,
                                   tBTTRC_PARAM_TYPE p2_type, UINTPTR p2_val,
                                   tBTTRC_PARAM_TYPE p3_type, UINTPTR p3_val,
                                   tBTTRC_PARAM_TYPE p4_type, UINTPTR p4_val);
EXPORT_API extern void BTTRC_StackTrace5(tBTTRC_LAYER_ID layer_id,
                                   tBTTRC_TYPE type,
                                   UINT16 token,
                                   tBTTRC_PARAM_TYPE p1_type, UINTPTR p1_val,
                                   tBTTRC_PARAM_TYPE p2_type, UINTPTR p2_val,
                                   tBTTRC_PARAM_TYPE p3_type, UINTPTR p3_val,
                                   tBTTRC_PARAM_TYPE p4_type, UINTPTR p4_val,
                                   tBTTRC_PARAM_TYPE p5_type, UINTPTR p5_val);
EXPORT_API extern void BTTRC_StackTrace6(tBTTRC_LAYER_ID layer_id,
                                   tBTTRC_TYPE type,
                                   UINT16 token,
                                   tBTTRC_PARAM_TYPE p1_type, UINTPTR p1_val,
                                   tBTTRC_PARAM_TYPE p2_type, UINTPTR p2_val,
                                   tBTTRC_PARAM_TYPE p3_type, UINTPTR p3_val,
                                   tBTTRC_PARAM_TYPE p4_type, UINTPTR p4_val,
                                   tBTTRC_PARAM_TYPE p5_type, UINTPTR p5_val,
                                   tBTTRC_PARAM_TYPE p6_type, UINTPTR p6_val);

#ifdef __cplusplus
}
#endif

/******************************************************************************
**
** Trace configurable parameters
**
******************************************************************************/

/* Enables or disables verbose trace information. */
#ifndef BT_TRACE_VERBOSE
#define BT_TRACE_VERBOSE    FALSE
#endif

/* Enables or disables all trace messages. */
#ifndef BT_USE_TRACES
#define BT_USE_TRACES       TRUE
#endif

/* Enables or disables protocol trace information. */
#ifndef BT_TRACE_PROTOCOL
#define BT_TRACE_PROTOCOL   FALSE
#endif

/******************************************************************************
**
** Trace Levels
**
** The following values may be used for different levels:
**      BT_TRACE_LEVEL_NONE    0        * No trace messages to be generated
**      BT_TRACE_LEVEL_ERROR   1        * Error condition trace messages
**      BT_TRACE_LEVEL_WARNING 2        * Warning condition trace messages
**      BT_TRACE_LEVEL_API     3        * API traces
**      BT_TRACE_LEVEL_EVENT   4        * Debug messages for events
**      BT_TRACE_LEVEL_DEBUG   5        * Debug messages (general)
******************************************************************************/

/* Core Stack default trace levels */
#ifndef HCI_INITIAL_TRACE_LEVEL
#define HCI_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_DEBUG
#endif

#ifndef BTM_INITIAL_TRACE_LEVEL
#define BTM_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_DEBUG
#endif

#ifndef L2CAP_INITIAL_TRACE_LEVEL
#define L2CAP_INITIAL_TRACE_LEVEL           BT_TRACE_LEVEL_DEBUG
#endif

#ifndef LLCP_INITIAL_TRACE_LEVEL
#define LLCP_INITIAL_TRACE_LEVEL            BT_TRACE_LEVEL_DEBUG
#endif

#ifndef RFCOMM_INITIAL_TRACE_LEVEL
#define RFCOMM_INITIAL_TRACE_LEVEL          BT_TRACE_LEVEL_DEBUG
#endif

#ifndef OBX_INITIAL_TRACE_LEVEL
#define OBX_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_DEBUG
#endif

#ifndef SDP_INITIAL_TRACE_LEVEL
#define SDP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_DEBUG
#endif

/* Profile default trace levels */
#ifndef DUN_INITIAL_TRACE_LEVEL
#define DUN_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_DEBUG
#endif

#ifndef GAP_INITIAL_TRACE_LEVEL
#define GAP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_DEBUG
#endif

#ifndef GOEP_INITIAL_TRACE_LEVEL
#define GOEP_INITIAL_TRACE_LEVEL            BT_TRACE_LEVEL_DEBUG
#endif

#ifndef HSP2_INITIAL_TRACE_LEVEL
#define HSP2_INITIAL_TRACE_LEVEL            BT_TRACE_LEVEL_DEBUG
#endif

#ifndef SPP_INITIAL_TRACE_LEVEL
#define SPP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_DEBUG
#endif

#ifndef BPP_INITIAL_TRACE_LEVEL
#define BPP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_DEBUG
#endif

#ifndef BIP_INITIAL_TRACE_LEVEL
#define BIP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_DEBUG
#endif

#ifndef BNEP_INITIAL_TRACE_LEVEL
#define BNEP_INITIAL_TRACE_LEVEL            BT_TRACE_LEVEL_DEBUG
#endif

#ifndef PAN_INITIAL_TRACE_LEVEL
#define PAN_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_DEBUG
#endif

#ifndef SAP_INITIAL_TRACE_LEVEL
#define SAP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_DEBUG
#endif

#ifndef FTP_INITIAL_TRACE_LEVEL
#define FTP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_DEBUG
#endif

#ifndef OPP_INITIAL_TRACE_LEVEL
#define OPP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_DEBUG
#endif

#ifndef HFP_INITIAL_TRACE_LEVEL
#define HFP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_DEBUG
#endif

#ifndef A2D_INITIAL_TRACE_LEVEL
#define A2D_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_DEBUG
#endif

#ifndef VDP_INITIAL_TRACE_LEVEL
#define VDP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_DEBUG
#endif

#ifndef AVDT_INITIAL_TRACE_LEVEL
#define AVDT_INITIAL_TRACE_LEVEL            BT_TRACE_LEVEL_DEBUG
#endif

#ifndef AVCT_INITIAL_TRACE_LEVEL
#define AVCT_INITIAL_TRACE_LEVEL            BT_TRACE_LEVEL_DEBUG
#endif

#ifndef AVRC_INITIAL_TRACE_LEVEL
#define AVRC_INITIAL_TRACE_LEVEL            BT_TRACE_LEVEL_DEBUG
#endif

#ifndef MCA_INITIAL_TRACE_LEVEL
#define MCA_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_DEBUG
#endif

#ifndef HID_INITIAL_TRACE_LEVEL
#define HID_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_DEBUG
#endif

/* Application and other default trace levels */
#ifndef RPC_INITIAL_TRACE_LEVEL
#define RPC_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_DEBUG
#endif

#ifndef APPL_INITIAL_TRACE_LEVEL
#define APPL_INITIAL_TRACE_LEVEL            BT_TRACE_LEVEL_DEBUG
#endif

#ifndef BT_TRACE_APPL
#define BT_TRACE_APPL   BT_USE_TRACES
#endif

#ifndef NFC_INITIAL_TRACE_LEVEL
#define NFC_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_DEBUG
#endif

#ifndef GATT_INITIAL_TRACE_LEVEL
#define GATT_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_DEBUG
#endif

#ifndef SMP_INITIAL_TRACE_LEVEL
#define SMP_INITIAL_TRACE_LEVEL             BT_TRACE_LEVEL_DEBUG
#endif






#define DRV_TRACE_ERROR0 printf
#define DRV_TRACE_ERROR1 printf
#define DRV_TRACE_ERROR2 printf
#define DRV_TRACE_ERROR3 printf
#define DRV_TRACE_ERROR4 printf
#define DRV_TRACE_ERROR5 printf
#define DRV_TRACE_ERROR6 printf

/* Driver Trace macros
*/
#define DRV_TRACE_DEBUG0 printf
#define DRV_TRACE_DEBUG1 printf
#define DRV_TRACE_DEBUG2 printf
#define DRV_TRACE_DEBUG3 printf
#define DRV_TRACE_DEBUG4 printf
#define DRV_TRACE_DEBUG5 printf
#define DRV_TRACE_DEBUG6 printf

#define APPL_TRACE_ERROR0 printf
#define APPL_TRACE_ERROR1 printf
#define APPL_TRACE_ERROR2 printf
#define APPL_TRACE_ERROR3 printf
#define APPL_TRACE_ERROR4 printf
#define APPL_TRACE_ERROR5 printf
#define APPL_TRACE_ERROR6 printf

#define APPL_TRACE_DEBUG0 printf
#define APPL_TRACE_DEBUG1 printf
#define APPL_TRACE_DEBUG2 printf
#define APPL_TRACE_DEBUG3 printf
#define APPL_TRACE_DEBUG4 printf
#define APPL_TRACE_DEBUG5 printf
#define APPL_TRACE_DEBUG6 printf




#endif /* BT_TRACE_H */


