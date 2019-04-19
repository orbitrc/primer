/*
//  String.cpp
//
//  Author:     Gene Ryu
//  Created:    2019. 04. 07. 18:09
//  Copyright (c) 2019 Gene Ryu. All rights reserved.
//
//
*/

#include <primer/String.h>

#include <iostream>

namespace pr {

String::String()
    : _str("")
{
}

String::String(const char* c_str)
    : _str(c_str)
{
}

String::String(const Base& object)
    : _str(object)
{
}

String String::operator+(const String& other) const
{
    return (this->_str + other._str).c_str();
}

} // namespace pr
