#include <primer/io.h>

#include <stdio.h>

#include <primer/format.h>

namespace pr {

void println(const String& str)
{
    printf("%s\n", str.c_str());
}

void println(const String& format_str, const String& str)
{
    auto s = format(format_str, str);
    printf("%s\n", s.c_str());
}

} // namespace pr
