#include "string.h"

#include <assert.h>
#include <string.h>

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

void string_starts_with()
{
    pr::String full = "Lorem ipsum dolor"_S;

    assert(full.starts_with("Lorem"_S));
}

void string_ends_with()
{
    pr::String full = "Lorem ipsum dolor"_S;

    assert(full.ends_with("dolor"_S));
}

void string_trim()
{
    pr::String str(" Hello, world!\t");

    assert(str.trim() == "Hello, world!"_S);
}

void string_split()
{
    pr::String str = "A;B;C"_S;
    pr::Vector<pr::String> split = str.split(";");

    assert(split.length() == 3);
    assert(split[0] == "A"_S);
    assert(split[1] == "B"_S);
    assert(split[2] == "C"_S);
}

void string_c_str()
{
    pr::String str = "Hello"_S;

    assert(strcmp(str.c_str(), "Hello") == 0);
}

void unicode_na()
{
    pr::Unicode::Scalar ga = 0xAC00;
    auto na = ga.na();

    assert(na == "HANGUL SYLLABLE GA");
}

} // namespace tests
