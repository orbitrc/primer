#ifndef _PRIMER_FORMAT_H
#define _PRIMER_FORMAT_H

#include <primer/string.h>

namespace pr {

/// Returns a new formatted string.
///
/// \since 0.4
/// \param format_str Format string.
/// \param str Format argument.
/// \return pr::String A new formatted string.
String format(const String& format_str, const String& str);

String format(const String& format_str, int8_t i);

String format(const String& format_str, uint8_t ui);

String format(const String& format_str, int16_t i);

String format(const String& format_str, uint16_t ui);

String format(const String& format_str, int32_t i);

String format(const String& format_str, uint32_t ui);

String format(const String& format_str, int64_t i);

String format(const String& format_str, uint64_t ui);

String format(const String& format_str, float f);

String format(const String& format_str, double d);

String format(const String& format_str, bool b);

template<typename T, typename... Args>
String format(const String& format_str, const T& val, Args... args)
{
    return format(format(format_str, val), args...);
}

} // namespace pr

#endif /* _PRIMER_FORMAT_H */
