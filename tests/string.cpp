#include "string.h"

#include <assert.h>
#include <string.h>

#include <primer/string.h>
#include <primer/byte-array.h>

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

void unicode_encoder_utf8()
{
    pr::String s = "가"_S;

    auto encoded = pr::Unicode::Encoder().encode(s);
    assert(encoded.length() == 3);
    assert(encoded[0] == 0xea);
    assert(encoded[1] == 0xb0);
    assert(encoded[2] == 0x80);
}

void unicode_encoder_utf16()
{
    // Under U+10000, Little-endian.
    {
        pr::String s = "7"_S; // U+0037

        auto scalars = s.unicode_scalars();
        assert(scalars[0] == 0x0037);

        auto encoded = pr::Unicode::Encoder(pr::Unicode::Encoding::Utf16Le)
            .encode(s);
        assert(encoded.length() == 2);
        assert(encoded[0] == 0x37);
        assert(encoded[1] == 0x00);
    }
    // Over U+FFFF, Little-endian.
    {
        pr::String s = "𐐷"_S; // U+10437

        auto encoded = pr::Unicode::Encoder(pr::Unicode::Encoding::Utf16Le)
            .encode(s);
        assert(encoded.length() == 4);
        assert(encoded[0] == 0x01);
        assert(encoded[1] == 0xD8);
        assert(encoded[2] == 0x37);
        assert(encoded[3] == 0xDC);
    }
    // Over U+FFFF, Big-endian.
    {
        pr::String s = "𐐷"_S; // U+10437

        auto encoded = pr::Unicode::Encoder(pr::Unicode::Encoding::Utf16Be)
            .encode(s);
        assert(encoded.length() == 4);
        assert(encoded[0] == 0xD8);
        assert(encoded[1] == 0x01);
        assert(encoded[2] == 0xDC);
        assert(encoded[3] == 0x37);
    }
}

void unicode_decoder_utf8()
{
    // Must succeed.
    pr::ByteArray encoded = {0xe3, 0x81, 0x93, 0xe3, 0x82, 0x93,
                             0xe3, 0x81, 0xb0, 0xe3, 0x82, 0x93,
                             0xe3, 0x81, 0xaf};
    pr::String aisatsu = "こんばんは"_S;

    pr::Unicode::Decoder decoder(pr::Unicode::Encoding::Utf8);
    pr::String decoded = decoder.decode(encoded);

    assert(decoded == aisatsu);

    // Must fail.
    {
        pr::ByteArray invalid = {0xC0, 0x80};
        bool failed = false;
        try {
            pr::String noop = decoder.decode(invalid);
        } catch (const pr::UnicodeDecodeError& e) {
            failed = true;
        }
        assert(failed == true);
    }
    // Must fail.
    {
        pr::ByteArray invalid = {0xF0, 0x80, 0x80, 0x80};
        bool failed = false;
        try {
            pr::String noop = decoder.decode(invalid);
        } catch (const pr::UnicodeDecodeError& e) {
            failed = true;
        }
        assert(failed == true);
    }
    // Must fail.
    {
        pr::ByteArray invalid = {0xF4, 0x90, 0x80, 0x80};
        bool failed = false;
        try {
            pr::String noop = decoder.decode(invalid);
        } catch (const pr::UnicodeDecodeError& e) {
            failed = true;
        }
        assert(failed == true);
    }
}

void unicode_decoder_utf16()
{
    // Must succeed.
    pr::ByteArray encoded_le = {0x7E, 0x30};
    pr::ByteArray encoded_be = {0x30, 0x7E};
    pr::String ma = "ま"_S;

    pr::Unicode::Decoder decoder_le(pr::Unicode::Encoding::Utf16Le);
    pr::Unicode::Decoder decoder_be(pr::Unicode::Encoding::Utf16Be);
    {
        pr::String decoded_le = decoder_le.decode(encoded_le);
        pr::String decoded_be = decoder_be.decode(encoded_be);
        assert(decoded_le == ma);
        assert(decoded_be == ma);
    }

    auto must_fail = [decoder_le, decoder_be](const pr::ByteArray& bytes,
                                              bool be) {
        bool failed = false;
        try {
            pr::String noop = (!be)
                ? decoder_le.decode(bytes)
                : decoder_be.decode(bytes);
        } catch (const pr::UnicodeDecodeError& e) {
            failed = true;
        }
        assert(failed == true);
    };

    // Must fail.
    {
        pr::ByteArray invalid = {0x00, 0xD8};
        must_fail(invalid, false);
    }
    // Must fail.
    {
        pr::ByteArray invalid = {0xD8, 0x00, 0x00, 0x41};
        must_fail(invalid, true);
    }
    // Must fail.
    {
        pr::ByteArray invalid = {0xAD, 0xDE, 0xEF, 0xBE};
        must_fail(invalid, false);
    }
    // Must succeed.
    {
        pr::ByteArray valid = {0x00, 0x11, 0x00, 0x00};
        bool failed = false;
        try {
            pr::String noop = decoder_be.decode(valid);
        } catch (const pr::UnicodeDecodeError& e) {
            failed = true;
        }
        assert(failed == false);
    }
}

} // namespace tests
