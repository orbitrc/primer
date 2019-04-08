//
//  Int.h
//
//  Author:     hardboiled65
//  Created:    2019. 01. 07. 20:26
//  Copyright (c) 2019 hardboiled65. All rights reserved.
//

/// \file
/// \brief  Integer types.
#ifndef _PR_INT_H
#define _PR_INT_H

#include <cstdint>

#include <primer/Base.h>

namespace pr {

class String;

/// \brief  8-bit signed integer.
class Int8 : public Base {
private:
    int8_t _int;
public:
    Int8();
    Int8(int8_t int8);
    // Int8& operator=(Int8& other);
    //==-------------------------
    // Examining an array
    //==-------------------------
    void contains() const;
    void count() const;

    //==-------------------------
    // Modifying
    //==-------------------------
    void append();

    operator int8_t() const { return _int; }
    operator String() const;

    //==--------------------------
    // Primer
    //==--------------------------
    const String repr() const;
};

} // namespace pr

#endif /* _PR_INT_H */
