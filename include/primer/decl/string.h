#ifndef _PRIMER_DECL_STRING_H
#define _PRIMER_DECL_STRING_H

#include <stdint.h>

#include <functional>
#include <string>
#include <exception>

namespace pr {

template<typename T>
class Vector;

//===========
// Unicode
//===========

class String;

class ByteArray;


/// \brief Exception for invalid values in the `Unicode::Scalar` constructor.
///
/// \since 0.5
///
/// If the given code point is over U+10FFFF, or is a surrogate character,
/// this exception is thrown.
class InvalidUnicodeScalarError : public std::exception
{
public:
    const char* what() const noexcept override;
};


/// \brief This exception thrown when decode byte array to string.
///
/// \since 0.5
///
/// Decoding may fail if the byte array is an ill-formed Unicode string or
/// not a string.
class UnicodeDecodeError : public std::exception
{
public:
    const char* what() const noexcept override;
};


class Unicode
{
public:

    /// \brief A Unicode scalar value is a code point that not exceeds
    /// U+10FFFF, and do not contain surrogate characters.
    class Scalar
    {
    public:

        /// \brief Construct `Unicode::Scalar` with a valid code point.
        ///
        /// If the given code point is an invalid scalar, then
        /// `InvalidUnicodeScalarError` will be thrown and the value
        /// will be set to 0.
        Scalar(uint32_t code_point);

        //=====================
        // Unicode Properties
        //=====================

        /// \brief Get Unicode 'na' property for the scalar.
        ///
        /// 'na' is the short name of 'Name' property. If the scalar has no
        /// this property then an empty `String` will be returned.
        String na() const;

        //==============
        // Conversions
        //==============
        operator uint32_t();
        operator uint32_t() const;

    private:
        uint32_t _code_point;
    };

    /// \brief Unicode encoding enum.
    ///
    /// \since 0.5
    enum class Encoding {
        Utf8,
        Utf16Le,
        Utf16Be,
    };

    /// \brief Unicode decoder.
    ///
    /// \since 0.5
    class Decoder
    {
    public:
        /// \brief Default constructor.
        ///
        /// The default encoding is UTF-8.
        Decoder();

        /// \brief Construct with encoding.
        Decoder(Encoding encoding);

        /// \brief Decode bytes and returns string.
        String decode(const ByteArray& bytes) const;

    private:
        Encoding _encoding;
    };

    /// \brief Unicode encoder.
    ///
    /// \since 0.5
    class Encoder
    {
    public:
        /// \brief Default constructor.
        ///
        /// The default encoding is UTF-8.
        Encoder();

        /// \brief Construct with encoding.
        Encoder(Encoding encoding);

        /// \brief Encode a string into bytes.
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

    /// \brief Contruct with empty string.
    String();

    /// \brief Construct with null-terminated string literal.
    String(const char *c_str);

    /// \brief Construct with C char array with length. Not null-terminated.
    String(const char *c_str, uint64_t len);

    /// \brief Copy constructor.
    String(const String& other);

    ~String();

    //=================
    // Element Access
    //=================

    /// \brief Return `Vector` of `Unicode::Scalar`.
    Vector<Unicode::Scalar> unicode_scalars() const;

    const char* c_str() const;

    //===============
    // Operations
    //===============

    /// \brief Split the string by the delimiter string.
    Vector<String> split(const String& delim) const;

    /// \brief Split the string by the delimiter string a given number
    /// of times.
    Vector<String> split(const String& delim, uint64_t count) const;

    /// \brief Returns new String that leading and trailing whitespaces removed.
    String trim() const;

    /// \brief Returns true if the string contains given string.
    bool contains(const String& other) const;

    /// \brief Returns true if the string starts with given string.
    bool starts_with(const String& other) const;

    /// \brief Returns true if the string ends with given string.
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
