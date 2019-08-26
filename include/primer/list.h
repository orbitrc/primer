/*
//  list.h
//
//  Author:     Gene Ryu
//  Created:    2019. 08. 18. 13:43
//  Copyright (c) 2019 Gene Ryu. All rights reserved.
//
//
*/
#ifndef _PR_LIST_H
#define _PR_LIST_H

#include "object.h"

struct pr_list;
typedef struct pr_list pr_list;

extern const pr_type *pr_list_t;

pr_list* pr_list_new(const pr_type *type);

void pr_list_push(pr_list *list, const void *val);

void pr_list_insert(pr_list *list, int64_t i, const void *val);

int64_t pr_list_count(pr_list *list);

void* pr_list_at(pr_list *list, int64_t i);

void* pr_list_pop(pr_list *list);

void pr_list_remove(pr_list *list, int64_t i);

#endif /* _PR_LIST_H */
