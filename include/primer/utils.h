//
//  utils.h
//
//  Author:     hardboiled65
//  Created:    2019. 04. 06. 20:01
//  Copyright (c) 2019 hardboiled65. All rights reserved.
//

/// \file
/// \brief  Utility functions.

#ifndef _PR_UTILS_H
#define _PR_UTILS_H

#include <primer/Base.h>

namespace pr {

class String;

void print(const Base& object);
void print(const String& str);

} // namespace pr

#endif /* _PR_UTILS_H */