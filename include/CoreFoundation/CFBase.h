/*
 *  CFBase.h
 *
 *  Author:     hardboiled65
 *  Created:    2017. 09. 13. 11:18
 *  Copyright (c) 2017 hardboiled65. All rights reserved.
 *
 *
 */

/*! \file
 *  \brief  Core Foundation base utilities.
 */
#ifndef _COREFOUNDATION_CFBASE_H
#define _COREFOUNDATION_CFBASE_H

#include <stdbool.h>
#include <stdint.h>

#ifndef CF_EXTERN_C_BEGIN
#ifdef __cplusplus
#define CF_EXTERN_C_BEGIN extern "C" {
#define CF_EXTERN_C_END }
#else
#define CF_EXTERN_C_BEGIN
#define CF_EXTERN_C_END
#endif

CF_EXTERN_C_BEGIN

#ifndef __CFBASICTYPES__
#define __CFBASICTYPES__
#ifndef __MACTYPES__
/*==-----------------
/ Base Integer Types
/-----------------==*/
typedef int8_t      SInt8;
typedef uint8_t     UInt8;
typedef int16_t     SInt16;
typedef uint16_t    UInt16;
typedef int32_t     SInt32;
typedef uint32_t    UInt32;
typedef int64_t     SInt64;
typedef uint64_t    UInt64;

/*==------------------------
/ Base Floating Point Types
/------------------------==*/
typedef float       Float32;
typedef double      Float64;

/*==------------
/ Boolean Types
/------------==*/
typedef unsigned char   Boolean;
#endif /* __MACTYPES__ */
#endif /* __CFBASICTYPES__ */

typedef unsigned long CFTypeID;
typedef const struct __CFString* CFStringRef;

/*==-------------------------------
/ Base Utilities
/----------------------------------
/ Base opaque types and functions.
/-------------------------------==*/

/*==---------
/ Data Types
/---------==*/

typedef long CFIndex;
typedef unsigned long CFOptionFlags;

typedef struct CFRange {
    CFIndex location;
    CFIndex length;
} CFRange;

/*==--------
/ Constants
/--------==*/

typedef enum CFComparisonResult {
    kCFCompareLessThan = -1L,
    kCFCompareEqualTo = 0,
    kCFCompareGreaterThan = 1,
} CFComparisonResult;

enum {
    kCFNotFound = -1;
};

/* extern */ const double kCFCoreFoundationVersionNumber = 0.0;

/*==-----------------------------------------------------
/ Core Foundation Base Utilities Miscellaneous Functions
/-----------------------------------------------------==*/

CFRange CFRangeMake(CFIndex loc, CFIndex len)
{
    CFRange range;
    range.location = loc;
    range.length = len;

    return range;
}

/*==--------
/ Callbacks
/--------==*/

typedef CFComparisonResult (*CFComparatorFunction)(const void *val1,
        const void *val2, void *context);

/*==-----------------------------------
/ CFAllocator
/--------------------------------------
/ Allocates and deallocates memory.
/-----------------------------------==*/

/*==--------
/ Callbacks
/--------==*/

typedef void* (*CFAllocatorAllocateCallBack)(CFIndex allocSize,
            CFOptionFlags hint, void *info);
typedef void* (*CFAllocatorReallocateCallBack)(void *ptr, CFIndex newsize,
            CFOptionFlags hint, void *info);
typedef void (*CFAllocatorDeallocateCallBack)(void *ptr, void *info);
typedef CFStringRef (*CFAllocatorCopyDescriptionCallBack)(const void *info);
typedef CFIndex (*CFAllocatorPreferredSizeCallBack)(CFIndex size,
            CFOptionFlags hint, void *info);
typedef const void* (*CFAllocatorRetainCallBack)(const void *info);
typedef void (*CFAllocatorReleaseCallBack)(const void *info);

/*==---------
/ Data Types
/---------==*/

typedef struct CFAllocatorContext {
    CFAllocatorAllocateCallBack allocate;
    CFAllocatorCopyDescriptionCallBack copyDescription;
    CFAllocatorDeallocateCallBack deallocate;
    void *info;
    CFAllocatorPreferredSizeCallBack preferredSize;
    CFAllocatorReallocateCallBack reallocate;
    CFAllocatorReleaseCallBack release;
    CFAllocatorRetainCallBack retain;
    CFIndex version;
} CFAllocatorContext;

typedef const struct __CFAllocatorRef* CFAllocatorRef;

/*==--------------------
/ Creating an Allocator
/--------------------==*/

CFAllocatorRef CFAllocatorCreate(CFAllocatorRef allocator,
        CFAllocatorContext *context);

/*==--------------------------------
/ Managing Memory with an Allocator
/--------------------------------==*/

void* CFAllocatorAllocate(CFAllocatorRef allocator, CFIndex size,
        CFOptionFlags hint);
void CFAllocatorDeallocate(CFAllocatorRef allocator, void *ptr);
CFIndex CFAllocatorGetPreferredSizeForSize(CFAllocatorRef allocator,
        CFIndex size, CFOptionFlags hint);
void* CFAllocatorReallocate(CFAllocatorRef allocator, void *ptr,
        CFIndex newsize, CFOptionFlags hint);

/*==----------------------------------------
/ Getting and Setting the Default Allocator
/----------------------------------------==*/

CFAllocatorRef CFAllocatorGetDefault();
void CFAllocatorSetDefault(CFAllocatorRef allocator);

/*==-----------------------------
/ Getting an Allocator's Context
/-----------------------------==*/

void CFAllocatorGetContext(CFAllocatorRef allocator,
        CFAllocatorContext *context);

/*==------------------------------
/ Getting the CFAllocator Type ID
/------------------------------==*/

CFTypeID CFAllocatorGetTypeID();

/*==--------
/ Constants
/--------==*/

/*! kCFAllocatorDefault
 *  \brief  A synonym for NULL.
 */
extern const CFAllocatorRef kCFAllocatorDefault;

/*! kCFAllocatorSystemDefault
 */
extern const CFAllocatorRef kCFAllocatorSystemDefault;

/*! kCFAllocatorMalloc
 */
extern const CFAllocatorRef kCFAllocatorMalloc;

/*! kCFAllocatorMallocZone
 */
extern const CFAllocatorRef kCFAllocatorMallocZone;

/*! kCFAllocatorNull
 */
extern const CFAllocatorRef kCFAllocatorNull;

/*! kCFAllocatorUseContext
 */
extern const CFAllocatorRef kCFAllocatorUseContext;

/*==-----------------------------------
/ CFType
/--------------------------------------
/ Base object of all CF opaque types.
/-----------------------------------==*/

/*==---------
/ Data Types
/---------==*/

typedef const void* CFTypeRef;
/*! CFTypeID
 */
/* Defined upper. */
typedef unsigned long CFHashCode;

/*==----------------
/ Memory Management
/----------------==*/

/*! CFGetAllocator
 *  \brief  Returns the allocator used to allocate a CF object.
 *  \param  cf
 *          The CFType object to examine.
 */
CFAllocatorRef CFGetAllocator(CFTypeRef cf);

/*! CFGetRetainCount
 *  \brief  Returns the reference count of a CF object.
 *  \param  cf
 *          The CFType object to examine.
 */
CFIndex CFGetRetainCount(CFTypeRef cf);

/*! CFMakeCollectable
 */
CFTypeRef CFMakeCollectable(CFTypeRef cf);

/*! CFRetain
 */
CFTypeRef CFRetain(CFTypeRef cf);

/*! CFRelease
 */
void CFRelease(CFTypeRef cf);

/*==-------------------
/ Determining Equality
/-------------------==*/

/*! CFEqual
 */
Boolean CFEqual(CFTypeRef cf1, CFTypeRef cf2);

/*==------
/ Hashing
/------==*/

/*! CFHash
 */
CFHashCode CFHash(CFTypeRef cf);

/*==----------------------
/ Miscellaneous Functions
/----------------------==*/

/*! CFCopyDescription
 */
CFStringRef CFCopyDescription(CFTypeRef cf);

/*! CFCopyTypeIDDescription
 */
CFStringRef CFCopyTypeIDDescription(CFTypeID type_id);

/*! CFGetTypeID
 */
CFTypeID CFGetTypeID(CFTypeRef cf);

/*! CFShow
 *  \brief  Prints a description of a CF object to stderr.
 */
void CFShow(CFTypeRef obj);


CF_EXTERN_C_END

#endif /* _COREFOUNDATION_CFBASE_H */
