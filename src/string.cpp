#include <primer/string.h>

#include <primer/core/string.h>

namespace pr {

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
