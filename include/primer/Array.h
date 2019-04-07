//
//  Array.h
//
//  Author:     hardboiled65
//  Created:    2018. 12. 31. 16:22
//  Copyright (c) 2018 hardboiled65. All rights reserved.
//

/// \file
/// \brief  Auto resizing array.
#ifndef _PR_ARRAY_H
#define _PR_ARRAY_H

#include <vector>

#include <primer/Base.h>

// for tests
#include <iostream>

namespace pr {

/// \brief  Array class.
/// \tparam T
///         Type of item.
template <typename T>
class Array : public Base {
private:
    std::vector<T> _vec;
public:
    Array()
    {
        std::cout << "Array created." << std::endl;
    }
    //==-------------------------
    // Examining an array
    //==-------------------------
    void contains() const;
    void size() const;

    //==-------------------------
    // Modifying
    //==-------------------------
    void push(const T& value)
    {
        this->_vec.push_back(value);
    }

};

} // namespace pr

#endif /* _PR_ARRAY_H */
