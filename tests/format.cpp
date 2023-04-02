#include "format.h"

#include <assert.h>

namespace tests {

void format()
{
    auto str1 = pr::format("The number is {}.", 666);

    assert(str1 == "The number is 666.");

    auto str2 = pr::format("{} {} {} {}"_S, 1, 2, 3, 4);

    assert(str2 == "1 2 3 4"_S);
}

} // namespace tests
