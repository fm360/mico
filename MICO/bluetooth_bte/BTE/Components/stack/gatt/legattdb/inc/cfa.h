/*******************************************************************************
* THIS INFORMATION IS PROPRIETARY TO
* BROADCOM CORP.
*-------------------------------------------------------------------------------
*
*           Copyright (c) 2003, 2004 Broadcom Corp.
*                      ALL RIGHTS RESERVED
*
********************************************************************************

********************************************************************************
*    File Name: cfa.h
*
*    Abstract:  Core Firmware API Definitions
*
*    Functions:
*            --
*
*    $History:$
*
*******************************************************************************/


#ifndef _CFA_H_
#define _CFA_H_


#include "types.h"

// DO NOT INCLUDE ANY OTHER HEADERS.  THIS HEADER NEEDS TO BE SUITABLE FOR
// EXTERNAL RELEASE!!!

#ifdef __cplusplus
extern "C" {
#endif

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// 10.4       Memory Manager (MM)
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void* cfa_mm_Alloc(UINT32 length);
// Allocates memory from the heap.

//------------------------------------------------------------------------------
void cfa_mm_Free(void *memoryBlock);
// Returns memory to the heap.

//------------------------------------------------------------------------------
void* cfa_mm_Sbrk(UINT32 length);
// Moves up the top of used memory by length, and returns a pointer to the 
// resulting space

UINT32 cfa_mm_MemFreeBytes(void);


#ifdef __cplusplus
}
#endif

#endif // _CFA_H_
