#include <primer/string.h>

#include <primer/core/string.h>
#include <primer/core/vector.h>

#include <primer/vector.h>
#include <primer/byte-array.h>

namespace pr {

const char* InvalidUnicodeScalarError::what() const noexcept
{
    return "The given code point exceeds U+10FFFF or is a surrogate character.";
}

//==========
// Unicode
//==========

String Unicode::version()
{
    return "15.0.0"_S;
}

Unicode::Scalar::Scalar(uint32_t code_point)
{
    if (code_point > 0x10FFFF) {
        this->_code_point = 0;
        throw InvalidUnicodeScalarError();
    }
    if (0xD800 <= code_point && code_point <= 0xDFFF) {
        this->_code_point = 0;
        throw InvalidUnicodeScalarError();
    }

    this->_code_point = code_point;
}

String Unicode::Scalar::na() const
{
    auto pr_s = pr_unicode_scalar_na(this->_code_point);
    String na = String(pr_string_c_str(pr_s));

    pr_string_free(pr_s);

    return na;
}

Unicode::Scalar::operator uint32_t()
{
    return this->_code_point;
}

Unicode::Scalar::operator uint32_t() const
{
    return this->_code_point;
}


Unicode::Encoder::Encoder()
{
    this->_encoding = Unicode::Encoding::Utf8;
}

Unicode::Encoder::Encoder(Encoding encoding)
{
    this->_encoding = encoding;
}

static ByteArray _unicode_encode_utf8(const Vector<Unicode::Scalar>& scalars)
{
    if (scalars.length() == 0) {
        return ByteArray();
    }

    uint64_t buffer_size = 0;
    // Count buffer size.
    for (auto& scalar: scalars) {
        if (scalar < 0x0080) {
            buffer_size += 1;
        } else if (scalar < 0x0800) {
            buffer_size += 2;
        } else if (scalar < 0x10000) {
            buffer_size += 3;
        } else {
            buffer_size += 4;
        }
    }

    uint8_t *buffer = new uint8_t[buffer_size];
    uint64_t buf_i = 0;
    // Encode each Unicode scalars.
    for (auto& scalar: scalars) {
        if (scalar < 0x0080) {
            buffer[buf_i++] = scalar;
        } else if (scalar < 0x0800) {
            buffer[buf_i++] = 0b11000000 | (scalar >> 6);
            buffer[buf_i++] = 0b10000000 | (scalar & 0b00111111);
        } else if (scalar < 0x10000) {
            buffer[buf_i++] = 0b11100000 | (scalar >> 12);
            buffer[buf_i++] = 0b10000000 | ((scalar >> 6) & 0b00111111);
            buffer[buf_i++] = 0b10000000 | (scalar & 0b00111111);
        } else {
            buffer[buf_i++] = 0b11110000 | (scalar >> 18);
            buffer[buf_i++] = 0b10000000 | ((scalar >> 12) & 0b00111111);
            buffer[buf_i++] = 0b10000000 | ((scalar >> 6) & 0b00111111);
            buffer[buf_i++] = 0b10000000 | (scalar & 0b00111111);
        }
    }
    ByteArray encoded = ByteArray(buffer, buffer_size);
    delete[] buffer;

    return encoded;
}

ByteArray Unicode::Encoder::encode(const String& string) const
{
    if (this->_encoding == Encoding::Utf8) {
        return _unicode_encode_utf8(string.unicode_scalars());
    } else if (this->_encoding == Encoding::Utf16Le) {
        // TODO.
        return ByteArray();
    } else {
        // TODO.
        return ByteArray();
    }
}

//========
// Impl
//========

class StringImpl
{
public:
    pr_string *_pr_string;
};

//===========
// String
//===========

String::String()
{
    this->_impl = new StringImpl;
    this->_impl->_pr_string = pr_string_new();
}

String::String(const char *c_str)
{
    this->_impl = new StringImpl;
    this->_impl->_pr_string = pr_string_from_c_str(c_str);
}

String::String(const char *c_str, uint64_t len)
{
    this->_impl = new StringImpl;
    this->_impl->_pr_string = pr_string_from_c_str_sized(c_str, len);
}

String::String(const String& other)
{
    this->_impl = new StringImpl;
    this->_impl->_pr_string = pr_string_cloned(other._impl->_pr_string);
}

String::~String()
{
    pr_string_free(this->_impl->_pr_string);
    delete this->_impl;
}


Vector<Unicode::Scalar> String::unicode_scalars() const
{
    pr_unicode_scalar_vector *pr_v = pr_string_unicode_scalars(
        this->_impl->_pr_string);

    Vector<Unicode::Scalar> v;
    for (uint64_t i = 0; i < pr_unicode_scalar_vector_length(pr_v); ++i) {
        uint32_t code_point = pr_unicode_scalar_vector_get(pr_v, i);
        Unicode::Scalar scalar(code_point);
        v.push(scalar);
    }

    pr_unicode_scalar_vector_free(pr_v);

    return v;
}

const char* String::c_str() const
{
    return pr_string_c_str(this->_impl->_pr_string);
}

Vector<String> String::split(const String& delim) const
{
    pr_string_vector *pr_v = pr_string_split(this->_impl->_pr_string,
        delim._impl->_pr_string);

    Vector<String> v;
    for (uint64_t i = 0; i < pr_string_vector_length(pr_v); ++i) {
        auto ptr = pr_string_vector_get(pr_v, i);
        auto string = String();
        pr_string_free(string._impl->_pr_string);
        string._impl->_pr_string = ptr;
        v.push(string);
    }

    pr_string_vector_free(pr_v);

    return v;
}

Vector<String> String::split(const String& delim, uint64_t count) const
{
    auto v = this->split(delim);
    if (v.length() <= count) {
        return v;
    }

    Vector<String> ret;
    auto len = v.length();
    decltype(len) i = 0;
    for (; i < count; ++i) {
        ret.push(v[i]);
    }
    String remains = v[i];
    ++i;
    for (; i < len; ++i) {
        remains = remains + delim + v[i];
    }
    ret.push(remains);

    return ret;
}

String String::trim() const
{
    String trimmed = String();
    pr_string_free(trimmed._impl->_pr_string);
    trimmed._impl->_pr_string = pr_string_trim(this->_impl->_pr_string);

    return trimmed;
}

bool String::contains(const String& other) const
{
    return pr_string_contains(this->_impl->_pr_string,
        other._impl->_pr_string);
}

bool String::starts_with(const String &other) const
{
    return pr_string_starts_with(this->_impl->_pr_string,
        other._impl->_pr_string);
}

bool String::ends_with(const String &other) const
{
    return pr_string_ends_with(this->_impl->_pr_string,
        other._impl->_pr_string);
}


String String::operator+(const String& other) const
{
    String ret;
    pr_string_free(ret._impl->_pr_string);
    ret._impl->_pr_string = pr_string_add(this->_impl->_pr_string,
        other._impl->_pr_string);

    return ret;
}

String& String::operator=(const String &other)
{
    pr_string_free(this->_impl->_pr_string);
    this->_impl->_pr_string = pr_string_cloned(other._impl->_pr_string);

    return *this;
}

bool String::operator==(const String& other) const
{
    return pr_string_eq(this->_impl->_pr_string, other._impl->_pr_string);
}

bool String::operator!=(const String& other) const
{
    return !(*this == other);
}

bool String::operator<(const String& other) const
{
    return pr_string_lt(this->_impl->_pr_string, other._impl->_pr_string);
}

bool String::operator>(const String& other) const
{
    return pr_string_gt(this->_impl->_pr_string, other._impl->_pr_string);
}

bool String::operator<=(const String& other) const
{
    bool lt = pr_string_lt(this->_impl->_pr_string, other._impl->_pr_string);

    return (lt || *this == other);
}

bool String::operator>=(const String& other) const
{
    bool gt = pr_string_gt(this->_impl->_pr_string, other._impl->_pr_string);

    return (gt || *this == other);
}

} // namespace pr

//===========
// Literals
//===========

pr::Unicode::Scalar operator""_U(unsigned long long int cp)
{
    return pr::Unicode::Scalar(cp);
}

pr::String operator""_S(const char *str, uint64_t len)
{
    pr::String ret(str, len);

    return ret;
}

