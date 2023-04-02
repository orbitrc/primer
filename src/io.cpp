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
    println(s);
}

void println(const String& format_str, int32_t i)
{
    auto s = format(format_str, i);
    println(s);
}

} // namespace pr
