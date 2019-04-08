/*
//  Int.cpp
//
//  Author:     hardboiled65
//  Created:    2019. 01. 07. 20:41
//  Copyright (c) 2019 hardboiled65. All rights reserved.
//
//
*/

#include <primer/Int.h>

#include <primer/String.h>
#include <primer/Exception.h>

namespace pr {

Int8::Int8()
    : _int(0)
{
}

Int8::Int8(int8_t int8)
    : _int(int8)
{
}

Int8::Int8(int i)
{
    if (i < -128 || 127 < i) {
        throw Exception();
    }
    Int8(static_cast<int8_t>(i));
}

/*
Int8& Int8::operator=(Int8& other)
{
    this->_int = other._int;

    return *this;
}
*/

Int8::operator String() const
{
    return "<Int>";
}

// const String Int8::repr() const
// {
//     return "<Int>";
// }


} // namespace pr
