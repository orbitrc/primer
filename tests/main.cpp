#include <iostream>
#include <cstdio>

#include <primer/primer.h>

int main()
{
    // Int
    pr::Int8 i = 1;

    printf("%d\n", i);
    pr::print(i);

    try {
        pr::Int8 i2 = 6666;
    } catch (const pr::Exception& err) {
        pr::print(pr::String("exception caught"));
    }

    // pr::Int8 i3 = 9999;

    // Array
    pr::Array<pr::Int8> a;
    a.push(i);
    pr::print(a);

    // String
    pr::String s = "Hello";

    return 0;
}
