#include <primer/string.h>

namespace pr {

String::String()
{
    this->_string = pr_string_new();
}

String::String(const char *c_str)
{
    this->_string = pr_string_from_c_str(c_str);
}

String::String(const char *c_str, uint64_t len)
{
    this->_string = pr_string_from_c_str_sized(c_str, len);
}

String::~String()
{
    pr_string_free(this->_string);
}


bool String::contains(const String& other) const
{
    return pr_string_contains(this->_string, other._string);
}

bool String::starts_with(const String &other) const
{
    return pr_string_starts_with(this->_string, other._string);
}

bool String::ends_with(const String &other) const
{
    return pr_string_ends_with(this->_string, other._string);
}

} // namespace pr
