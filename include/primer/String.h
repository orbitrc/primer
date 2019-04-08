//
//  String.h
//
//  Author:     Gene Ryu
//  Created:    2019. 04. 07. 17:49
//  Copyright (c) 2019 Gene Ryu. All rights reserved.
//

/// \file
/// \brief  String class.
#ifndef _PR_STRING_H
#define _PR_STRING_H

#include <primer/Base.h>

#include <string>
#include <vector>

namespace pr {

/// \brief  String class.
class String : public Base {
private:
    std::string _str;
public:
    String();

    String(const char* c_str);

    //==-------------------------
    // Examining a string
    //==-------------------------
    int size() const;

    //==-------------------------
    // Modifying
    //==-------------------------
    String operator+(const String& other) const;

    operator const char*() const { return _str.c_str(); }

    //==--------------------------
    // Primer
    //==--------------------------
    // const char* repr() const;
};

} // namespace pr

#endif /* _PR_STRING_H */
