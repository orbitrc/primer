#include <primer/string.h>

int main(int argc, char *argv[])
{
    bool passed = false;
    pr::String s1 = "Foo"_S;
    pr::String s2 = "Foo"_S;

    passed = s1 == s2;
    if (!passed) {
        return 1;
    }

    pr::String s3 = "Bar"_S;

    passed = s1 != s3;
    if (!passed) {
        return 1;
    }

    passed = (s1 > s3);
    if (!passed) {
        return 1;
    }
    passed = (s3 < s1);
    if (!passed) {
        return 1;
    }
    passed = (s1 <= s2);
    if (!passed) {
        return 1;
    }
    passed = (s1 >= s2);
    if (!passed) {
        return 1;
    }

    return 0;
}
