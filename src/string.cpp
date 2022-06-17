#include <primer/string.h>

#include <primer/core/string.h>
#include <primer/core/vector.h>

namespace pr {

//==========
// Unicode
//==========

String Unicode::version()
{
    return "14.0.0"_S;
}

Unicode::Scalar::Scalar(uint32_t code_point)
{
    // TODO: Check if code point is surrogate.

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

Unicode::Scalar::operator const uint32_t() const
{
    return this->_code_point;
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

    return v;
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

bool String::operator==(const String& other)
{
    return pr_string_eq(this->_impl->_pr_string, other._impl->_pr_string);
}

bool String::operator!=(const String& other)
{
    return !(*this == other);
}

} // namespace pr

//===========
// Literals
//===========

pr::String operator""_S(const char *str, uint64_t len)
{
    pr::String ret(str, len);

    return ret;
}
