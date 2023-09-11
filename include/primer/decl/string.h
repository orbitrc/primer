#ifndef _PRIMER_DECL_STRING_H
#define _PRIMER_DECL_STRING_H

#include <stdint.h>

#include <functional>
#include <string>

namespace pr {

template<typename T>
class Vector;

//===========
// Unicode
//===========

class String;

class ByteArray;

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
        operator uint32_t() const;

    private:
        uint32_t _code_point;
    };

    /// Unicode encoding enum.
    ///
    /// \since 0.5
    enum class Encoding {
        Utf8,
        Utf16Le,
        Utf16Be,
    };

    /// Unicode decoder.
    ///
    /// \since 0.5
    class Decoder
    {
    public:
        Decoder();

        Decoder(Encoding encoding);

        String decode(const ByteArray& bytes) const;

    private:
        Encoding _encoding;
    };

    /// Unicode encoder.
    ///
    /// \since 0.5
    class Encoder
    {
    public:
        Encoder();

        Encoder(Encoding encoding);

        ByteArray encode(const String& string) const;

    private:
        Encoding _encoding;
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

    /// Construct with C char array with length. Not null-terminated.
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

    Vector<String> split(const String& delim, uint64_t count) const;

    /// Returns new String that leading and trailing whitespaces removed.
    String trim() const;

    /// Returns true if the string contains given string.
    bool contains(const String& other) const;

    /// Returns true if the string starts with given string.
    bool starts_with(const String& other) const;

    /// Returns true if the string ends with given string.
    bool ends_with(const String& other) const;

    //===============
    // Operators
    //===============

    String operator+(const String& other) const;

    String& operator=(const String& other);

    bool operator==(const String& other) const;

    bool operator!=(const String& other) const;

    bool operator<(const String& other) const;

    bool operator>(const String& other) const;

    bool operator<=(const String& other) const;

    bool operator>=(const String& other) const;

private:
    StringImpl *_impl;
};

} // namespace pr

//===============
// Literals
//===============

pr::Unicode::Scalar operator""_U(unsigned long long int);

pr::String operator""_S(const char *str, uint64_t len);

//=========
// Hash
//=========

template<>
struct std::hash<pr::String>
{
    std::size_t operator()(const pr::String& s) const
    {
        return std::hash<std::string>()(s.c_str());
    }
};

#endif // _PRIMER_DECL_STRING_H
