#include <iostream>
#include <cstdio>

#include <primer/primer.h>

int main()
{
    // Int
    pr::Int8 i = 1;

    printf("%d\n", i);
    pr::print(i);

    // Array
    pr::Array<pr::Int8> a;
    a.push(i);

    return 0;
}
