#ifndef _PRIMER_IO_H
#define _PRIMER_IO_H

#include <primer/string.h>

namespace pr {

void println(const pr::String& str);

void println(const pr::String& format_str, const pr::String& str);

} // namespace pr

#endif /* _PRIMER_IO_H */
