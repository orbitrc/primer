#ifndef _PRIMER_IO_H
#define _PRIMER_IO_H

#include <primer/string.h>

namespace pr {

/// Prints string to the standard output.
///
/// \since 0.4
void println(const pr::String& str);

void println(const pr::String& format_str, const pr::String& str);

void println(const pr::String& format_str, int32_t i);

} // namespace pr

#endif /* _PRIMER_IO_H */
