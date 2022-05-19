#ifndef _PRIMER_STRING_H
#define _PRIMER_STRING_H

#include <stdint.h>

namespace pr {

class StringImpl;

class String
{
public:
    //=========================
    // Constructor/Destructor
    //=========================

    String();

    String(const char *c_str);

    String(const char *c_str, uint64_t len);

    String(const String& other);

    ~String();

    //===============
    // Operations
    //===============

    bool contains(const String& other) const;

    bool starts_with(const String& other) const;

    bool ends_with(const String& other) const;

    //===============
    // Operators
    //===============

    String& operator=(const String& other);

private:
    StringImpl *_impl;
};

} // namespace pr

//===============
// Literals
//===============

pr::String operator""_S(const char *str, uint64_t len);

#endif // _PRIMER_STRING_H
