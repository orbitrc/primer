/*
//  object.h
//
//  Author:     Gene Ryu
//  Created:    2019. 08. 18. 13:29
//  Copyright (c) 2019 Gene Ryu. All rights reserved.
//
//
*/
#ifndef _PR_OBJECT_H
#define _PR_OBJECT_H

#include <stdint.h>

enum pr_object_base {
    PR_CLASS    = 1,
    PR_STRUCT   = 2,
};

struct pr_object {
    enum pr_object_base base;
    uint64_t rc;
};
typedef struct pr_object pr_object;

struct pr_type {
    const char *name;
    uint16_t size;
};
typedef struct pr_type pr_type;

void pr_object_ref(pr_object *obj);

void pr_object_deref(pr_object *obj);

#endif /* _PR_OBJECT_H */
