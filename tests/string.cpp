#include "string.h"

#include <assert.h>

#include <primer/string.h>

namespace tests {

void string_contains()
{
    pr::String str("Lorem ipsum dolor");
    pr::String ipsum("ipsum");

    assert(str.contains(ipsum));
}

} // namespace tests
