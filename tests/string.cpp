#include "string.h"

#include <assert.h>

#include <primer/string.h>

namespace tests {

void string_compare()
{
    pr::String s1 = "Foo"_S;
    pr::String s2 = "Foo"_S;

    assert(s1 == s2);

    pr::String s3 = "Bar"_S;

    assert(s1 != s3);
}

void string_contains()
{
    pr::String str("Lorem ipsum dolor");
    pr::String ipsum("ipsum");

    assert(str.contains(ipsum));
}

} // namespace tests
