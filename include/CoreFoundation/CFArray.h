/*
 *  CFArray.h
 *
 *  Author:     <OWNER>
 *  Created:    2017. 09. 14. 17:00
 *  Copyright (c) 2016 <OWNER>. All rights reserved.
 *
 *
 */

/*! \file
 *  \brief  Array.
 */
#ifndef _COREFOUNDATION_CFARRAY_H
#define _COREFOUNDATION_CFARRAY_H

#include <CoreFoundation/CFBase.h>

CF_EXTERN_C_BEGIN

/*==--------
/ Callbacks
/--------==*/

/*! CFArrayApplierFunction
 */
typedef void (*CFArrayApplierFunction)(const void *value, void *context);

/*! CFArrayCopyDescriptionCallBack
 */
typedef CFStringRef (*CFArrayCopyDescriptionCallBack)(const void *value);

/*! CFArrayEqualCallBack
 */
typedef Boolean (*CFArrayEqualCallBack)(const void *value1, const void *value2);

/*! CFArrayReleaseCallBack
 */
typedef void (*CFArrayReleaseCallBack)(CFAllocatorRef allocator,
            const void *value);

/*! CFArrayRetainCallBack
 */
typedef const void* (*CFArrayRetainCallBack)(CFAllocatorRef allocator,
            const void *value);

typedef struct CFArrayCallBacks {
    CFArrayCopyDescriptionCallBack copyDescription;
    CFArrayEqualCallBack equal;
    CFArrayReleaseCallBack release;
    CFArrayRetainCallBack retain;
    CFIndex version;
} CFArrayCallBacks;

extern const CFArrayCallBacks kCFTypeArrayCallBacks;

typedef const struct __CFArray* CFArrayRef;

/*==----------------
/ Creating an Array
/----------------==*/

/*! CFArrayCreate
 *  \brief  Creates a new immutable array.
 *  \param  allocator
 *  \param  values
 *  \param  numValues
 *  \param  callBacks
 */
CFArrayRef CFArrayCreate(CFAllocatorRef allocator, const void **values,
        CFIndex numValues, const CFArrayCallBacks *callBacks);

/*! CFArrayCreateCopy
 *  \brief  Creates a new immutable array copied from another array.
 *  \param  allocator
 *  \param  theArray
 */
CFArrayRef CFArrayCreateCopy(CFAllocatorRef allocator, CFArrayRef theArray);

/*==-----------------
/ Examining an Array
/-----------------==*/

/*! CFArrayBSearchValues
 */
CFIndex CFArrayBSearchValues(CFArrayRef theArray, CFRange range,
        const void *value, CFComparatorFunction comparator, void *context);

/*! CFArrayContainsValue
 */
Boolean CFArrayContainsValue(CFArrayRef theArray, CFRange range,
        const void *value);

/*! CFArrayGetCount
 */
CFIndex CFArrayGetCount(CFArrayRef theArray);

/*! CFArrayGetCountOfValue
 */
CFIndex CFArrayGetCountOfValue(CFArrayRef theArray, CFRange range,
        const void *value);

/*! CFArrayGetFirstIndexOfValue
 */
CFIndex CFArrayGetFirstIndexOfValue(CFArrayRef theArray, CFRange range,
        const void *value);

/*! CFArrayGetLastIndexOfValue
 */
CFIndex CFArrayGetLastIndexOfValue(CFArrayRef theArray, CFRange range,
        const void *value);

/*! CFArrayGetValues
 */
void CFArrayGetValues(CFArrayRef theArray, CFRange range, const void **values);

/*! CFArrayGetValuesAtIndex
 */
const void* CFArrayGetValuesAtIndex(CFArrayRef theArray, CFIndex idx);

/*==------------------------------
/ Applying a Function to Elements
/------------------------------==*/

/*! CFArrayApplyFunction
 */
void CFArrayApplyFunction(CFArrayRef theArray, CFRange range,
        CFArrayApplyFunction applier, void *context);

/*==--------------------------
/ Getting the CFArray Type ID
/--------------------------==*/

/*! CFArrayGetTypeID
 */
CFTypeID CFArrayGetTypeID();

typedef struct __CFArray* CFMutableArray;

/*==-------------------------------------
/ CFMutableArray Miscellaneous Functions
/-------------------------------------==*/

/*! CFArrayAppendArray
 */
void CFArrayAppendArray(CFMutableArrayRef theArray, CFArrayRef otherArray,
        CFRange otherRange);

/*! CFArrayAppendValue
 */
void CFArrayAppendValue(CFMutableArrayRef theArray, const void *value);

/*! CFArrayCreateMutable
 */
CFMutableArrayRef CFArrayCreateMutable(CFAllocatorRef allocator,
        CFIndex capacity, const CFArrayCallBacks *callBacks);

/*! CFArrayCreateMutableCopy
 */
CFMutableArrayRef CFArrayCreateMutableCopy(CFAllocatorRef allocator,
        CFIndex capacity, CFArrayRef theArray);

/*! CFArrayExchangeValuesAtIndices
 */
void CFArrayExchangeValuesAtIndices(CFMutableArrayRef theArray,
        CFIndex idx1, CFIndex idx2);

/*! CFArrayInsertValueAtIndex
 */
void CFArrayInsertValueAtIndex(CFMutableArrayRef theArray, CFIndex idx,
        const void *value);

/*! CFArrayRemoveAllValues
 */
void CFArrayRemoveAllValues(CFMutableArrayRef theArray);

/*! CFArrayRemoveValueAtIndex
 */
void CFArrayRemoveValueAtIndex(CFMutableArrayRef theArray, CFIndex idx);

/*! CFArrayReplaceValues
 */
void CFArrayReplaceValues(CFMutableArrayRef theArray, CFRange range,
        const void **newValues, CFIndex newCount);

/*! CFArraySetValueAtIndex
 */
void CFArraySetValueAtIndex(CFMutableArrayRef theArray, CFIndex idx,
        const void *value);

/*! CFArraySortValues
 */
void CFArraySortValues(CFMutableArrayRef theArray, CFRange range,
        CFComparatorFunction comparator, void *context);

CF_EXTERN_C_END

#endif /* _COREFOUNDATION_CFARRAY_H */
