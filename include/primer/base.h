/*
//  base.h
//
//  Author:     Gene Ryu
//  Created:    2019. 10. 04. 18:39
//  Copyright (c) 2019 Gene Ryu. All rights reserved.
//
//
*/
#ifndef _PR_BASE_H
#define _PR_BASE_H

#include <stdint.h>

enum pr_object_base {
    PR_CLASS    = 1,
    PR_STRUCT   = 2,
};

struct pr_object {
    enum pr_object_base base;
    uint64_t rc;
    void (*destructor)(struct pr_object*);
};
typedef struct pr_object pr_object;

void pr_object_ref(pr_object *obj);

void pr_object_deref(pr_object *obj);


struct pr_type {
    const char *name;
    uint16_t size;
};
typedef struct pr_type pr_type;


// Integer type
typedef int64_t pr_int;
extern const pr_type *pr_int_t;


// Real number type
typedef double  pr_real;
extern const pr_type *pr_real_t;

#endif /* _PR_BASE_H */
