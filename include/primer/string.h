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

    ~String();

    //===============
    // Operations
    //===============

    bool contains(const String& other) const;

    bool starts_with(const String& other) const;

    bool ends_with(const String& other) const;

private:
    StringImpl *_impl;
};

} // namespace pr

#endif // _PRIMER_STRING_H
