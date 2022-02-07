#include "range.h"

#include <assert.h>

namespace tests {

void range_contains()
{
    pr::Range r1(2, 42);

    assert(r1.contains(41));
    assert(!r1.contains(42));
}

void range_random()
{
    pr::Range r1(-10, 10);

    assert(r1.random() >= -10 && r1.random() < 10);
}

} // namespace tests
