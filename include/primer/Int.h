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

namespace pr {

/// \brief  8-bit signed integer.
class Int8 {
private:
    int8_t _int;
public:
    Int8();
    Int8(int8_t int8);
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
};

} // namespace pr

#endif /* _PR_INT_H */
