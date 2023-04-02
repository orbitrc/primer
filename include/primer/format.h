#ifndef _PRIMER_FORMAT_H
#define _PRIMER_FORMAT_H

#include <primer/string.h>

namespace pr {

String format(const String& format_str, const String& str);

String format(const String& format_str, int32_t i);

template<typename T, typename... Args>
String format(const String& format_str, const T& val, Args... args)
{
    return format(format(format_str, val), args...);
}

} // namespace pr

#endif /* _PRIMER_FORMAT_H */
