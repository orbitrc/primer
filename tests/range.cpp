#include "range.h"

#include <assert.h>

namespace tests {

void range_getters()
{
    pr::Range r1(3, 14);

    assert(r1.start() == 3);
    assert(r1.end() == 14);
    assert(r1.exclusive() == true);
}

void range_contains()
{
    pr::Range r1(2, 42);

    assert(r1.contains(41));
    assert(!r1.contains(42));

    pr::Range r2(0, 10, false);

    assert(r2.contains(10));
}

void range_random()
{
    pr::Range r1(-10, 10);

    assert(r1.random() >= -10 && r1.random() < 10);
}

void range_copy()
{
    pr::Range r1(0, 10);
    pr::Range r2 = r1;
}

} // namespace tests
