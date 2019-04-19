/*
//  utils.cpp
//
//  Author:     Gene Ryu
//  Created:    2019. 04. 06. 20:03
//  Copyright (c) 2019 Gene Ryu. All rights reserved.
//
//
*/
#include <primer/utils.h>

#include <primer/String.h>

#include <iostream>

namespace pr {


void print(const String& str)
{
    std::cout << str << std::endl;
}

} // namespace pr