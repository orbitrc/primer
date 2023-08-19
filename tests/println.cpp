#include <primer/io.h>
#include <primer/range.h>

int main(int argc, char *argv[])
{
    pr::println("Hello, {}. You're number is {}. You are human: {}."_S,
        "there"_S, 42, true);

    pr::Range rng(0, 10, false);
    pr::println("{}", rng);

    return 0;
}
