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

    assert(s1 > s3);
    assert(s3 < s1);
    assert(s1 <= s2);
    assert(s1 >= s2);
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

    pr::String str2 = "A-B-C-D"_S;
    auto split2 = str2.split("-"_S, 2);

    assert(split2.length() == 3);
    assert(split2[0] == "A"_S);
    assert(split2[1] == "B"_S);
    assert(split2[2] == "C-D"_S);

    auto split3 = str2.split("-", 6);

    assert(split3.length() == 4);
}

void string_c_str()
{
    pr::String str = "Hello"_S;

    assert(strcmp(str.c_str(), "Hello") == 0);
}

void string_add()
{
    pr::String src = "Lorem"_S;

    pr::String dst = src + " ipsum"_S + " dolor"_S;

    assert(dst == "Lorem ipsum dolor"_S);
}

void string_unicode_scalars()
{
    pr::String s = "A가"_S;

    auto scalars = s.unicode_scalars();

    assert(scalars.length() == 2);
    assert(scalars[0] == 0x0041);
    assert(scalars[1] == 0xAC00);
}

void unicode_scalar_compare()
{
    pr::Unicode::Scalar b = U'b';

    assert(b == U'b');

    pr::String s = "ABCD"_S;

    const auto scalars = s.unicode_scalars();

    assert(scalars[0] == U'A');
}

void unicode_na()
{
    pr::Unicode::Scalar ga = 0xAC00;
    auto na = ga.na();

    assert(na == "HANGUL SYLLABLE GA");
}

void unicode_scalar_literal()
{
    auto space = 0x0020_U;

    assert(space == 0x0020);
}

} // namespace tests
