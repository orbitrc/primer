/*
 *  CFBag.h
 *
 *  Author:     <OWNER>
 *  Created:    2017. 09. 15. 05:14
 *  Copyright (c) 2017 <OWNER>. All rights reserved.
 *
 *
 */

/*! \file
 *  \brief  Bag.
 */
#ifndef _COREFOUNDATION_CFBAG_H
#define _COREFOUNDATION_CFBAG_H

#include <CoreFoundation/CFBase.h>

CF_EXTERN_C_BEGIN

/*==--------
/ Callbacks
/--------==*/

/*! CFBagApplierFunction
 */
typedef void (*CFBagApplierFunction)(const void *value, void *context);

/*! CFBagCopyDescriptionCallBack
 */
typedef CFStringRef (*CFBagCopyDescriptionCallBack)(const void *value);

/*! CFBagEqualCallBack
 */
typedef Boolean (*CFBagEqualCallBack)(const void *value1, const void *value2);

/*! CFBagHashCallBack
 */
typedef CFHashCode (*CFBagHashCallBack)(const void *value);

/*! CFBagReleaseCallBack
 */
typedef void (*CFBagReleaseCallBack)(CFAllocatorRef allocator,
            const void *value);

/*! CFBagRetainCallBack
 */
typedef const void* (*CFBagRetainCallBack)(CFAllocatorRef allocator,
            const void *value);

typedef struct CFBagCallBacks {
    CFBagCopyDescriptionCallBack copyDescription;
    CFBagEqualCallBack equal;
    CFBagHashCallBack hash;
    CFBagRetainCallBack release;
    CFBagRetainCallBack retain;
    CFIndex version;
} CFBagCallBacks;

extern const CFBagCallBacks kCFTypeBagCallBacks;
extern const CFBagCallBacks kCFCopyStringBagCallBacks;

typedef const struct __CFBag* CFBagRef;

/*==-------------
/ Creating a Bag
/-------------==*/

/*! CFBagCreate
 */
CFBagRef CFBagCreate(CFAllocatorRef allocator, const void **values,
        CFIndex numValues, const CFBagCallBacks *callBacks);

/*! CFBagCreateCopy
 */
CFBagRef CFBagCreateCopy(CFAllocatorRef allocator, CFBagRef theBag);

/*==--------------
/ Examining a Bag
/--------------==*/

/*! CFBagContainsValue
 */
Boolean CFBagContainsValue(CFBagRef theBag, const void *value);

/*! CFBagGetCount
 */
CFIndex CFBagGetCount(CFBagRef theBag);

/*! CFBagGetCountOfValue
 */
CFIndex CFBagGetCountOfValue(CFBagRef theBag, const void *value);

/*! CFBagGetValue
 */
const void* CFBagGetValue(CFBagRef theBag, const void *value);

/*! CFBagGetValueIfPresent
 */
Boolean CFBagGetValueIfPresent(CFBagRef theBag, const void *candidate,
        const void **value);

/*! CFBagGetValues
 */
void CFBagGetValues(CFBagRef theBag, const void **values);

/*==-------------------------------------------
/ Applying a Function to the Contents of a Bag
/-------------------------------------------==*/

/*! CFBagApplyFunction
 */
void CFBagApplyFunction(CFBagRef theBag, CFBagApplierFunction applier,
        void *context);

/*==------------------------
/ Getting the CFBag Type ID
/------------------------==*/

/*! CFBagGetTypeID
 */
CFTypeID CFBagGetTypeID();

typedef struct __CFBag* CFMutableBagRef;

/*==---------------------
/ Creating a Mutable Bag
/---------------------==*/

/*! CFBagCreateMutable
 */
CFMutableBagRef CFBagCreateMutable(CFAllocatorRef allocator, CFIndex capacity,
        const CFBagCallBacks *callBacks);

/*! CFBagCreateMutableCopy
 */
CFMutableBagRef CFBagCreateMutableCopy(CFAllocatorRef allocator,
        CFIndex capacity, CFBagRef theBag);

/*==----------------------
/ Modifying a Mutable Bag
/----------------------==*/

/*! CFBagAddValue
 */
void CFBagAddValue(CFMutableBagRef theBag, const void *value);

/*! CFBagRemoveAllValues
 */
void CFBagRemoveAllValues(CFMutableBagRef theBag);

/*! CFBagRemoveValue
 */
void CFBagRemoveValue(CFMutableBagRef theBag, const void *value);

/*! CFBagReplaceValue
 */
void CFBagReplaceValue(CFMutableBagRef theBag, const void *value);

/*! CFBagSetValue
 */
void CFBagSetValue(CFMutableBagRef theBag, const void *value);

CF_EXTERN_C_END

#endif /* _COREFOUNDATION_CFBAG_H */
