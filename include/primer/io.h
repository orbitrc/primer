#ifndef _PRIMER_IO_H
#define _PRIMER_IO_H

#include <primer/string.h>

#include <stdint.h>

#include <primer/format.h>

namespace pr {

/// Prints string to the standard output with trailing newline.
///
/// \since 0.4
void println(const pr::String& str);

void println(const pr::String& format_str, const pr::String& str);

void println(const pr::String& format_str, int32_t i);

template<typename T, typename... Args>
void println(const pr::String& format_str, const T& val, Args... args)
{
    println(format(format_str, val, args...));
}

/// Prints string to the standard error with trailing newline.
///
/// \since 0.4
void eprintln(const pr::String& str);

template<typename T, typename... Args>
void eprintln(const pr::String& format_str, const T& val, Args... args)
{
    eprintln(format(format_str, val, args...));
}

} // namespace pr

#endif /* _PRIMER_IO_H */
