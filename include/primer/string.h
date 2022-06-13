#ifndef _PRIMER_STRING_H
#define _PRIMER_STRING_H

#include <stdint.h>

#include <primer/vector.h>

namespace pr {

//===========
// Unicode
//===========

class String;

class Unicode
{
public:

    class Scalar
    {
    public:

        Scalar(uint32_t code_point);

        //=====================
        // Unicode Properties
        //=====================
        String na() const;

        //==============
        // Conversions
        //==============
        operator uint32_t();

    private:
        uint32_t _code_point;
    };

public:

    Unicode() = delete;

    static String version();
};

//===========
// String
//===========

class StringImpl;

class String
{
public:
    //=========================
    // Constructor/Destructor
    //=========================

    /// Contruct with empty string.
    String();

    /// Construct with null-terminated string literal.
    String(const char *c_str);

    String(const char *c_str, uint64_t len);

    String(const String& other);

    ~String();

    //=================
    // Element Access
    //=================

    Vector<Unicode::Scalar> unicode_scalars() const;

    const char* c_str() const;

    //===============
    // Operations
    //===============

    Vector<String> split(const String& delim) const;

    /// Returns new String that leading and trailing whitespaces removed.
    String trim() const;

    bool contains(const String& other) const;

    bool starts_with(const String& other) const;

    bool ends_with(const String& other) const;

    //===============
    // Operators
    //===============

    String operator+(const String& other) const;

    String& operator=(const String& other);

    bool operator==(const String& other);

    bool operator!=(const String& other);

private:
    StringImpl *_impl;
};

} // namespace pr

//===============
// Literals
//===============

pr::String operator""_S(const char *str, uint64_t len);

#endif // _PRIMER_STRING_H
