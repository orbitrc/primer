#ifndef _PRIMER_FORMAT_H
#define _PRIMER_FORMAT_H

#include <primer/string.h>

namespace pr {

String format(const String& format_str, const String& str);

String format(const String& format_str, int32_t i);

} // namespace pr

#endif /* _PRIMER_FORMAT_H */
