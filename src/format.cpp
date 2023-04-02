#include <primer/format.h>

#include <string>

namespace pr {

String format(const String& format_str, const String& str)
{
    auto split = format_str.split("{}"_S, 1);
    if (split.length() < 2) {
        return format_str;
    }

    return split[0] + str + split[1];
}

String format(const String& format_str, int32_t i)
{
    auto split = format_str.split("{}"_S, 1);
    if (split.length() < 2) {
        return format_str;
    }

    auto std_str = std::to_string(i);

    return split[0] + String(std_str.c_str()) + split[1];
}

} // namespace pr
