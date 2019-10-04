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

#include "base.h"

#include <stdint.h>


void pr_object_ref(pr_object *obj);

void pr_object_deref(pr_object *obj);

#endif /* _PR_OBJECT_H */
