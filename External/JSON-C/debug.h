/*
 * $Id: debug.h,v 1.5 2006/01/30 23:07:57 mclark Exp $
 *
 * Copyright (c) 2004, 2005 Metaparadigm Pte. Ltd.
 * Michael Clark <michael@metaparadigm.com>
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See COPYING for details.
 *
 */

#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif


#define MC_ABORT(x, ...) if (0) custom_log("JSON-abort", x, ##__VA_ARGS__)
#define MC_DEBUG(x, ...) if (0) custom_log("JSON-debug", x, ##__VA_ARGS__)
#define MC_ERROR(x, ...) if (0) custom_log("JSON-error", x, ##__VA_ARGS__)
#define MC_INFO(x, ...) if (0) custom_log("JSON-info", x, ##__VA_ARGS__)


#ifdef __cplusplus
}
#endif

#endif

