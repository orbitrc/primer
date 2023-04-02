#include <primer/io.h>

int main(int argc, char *argv[])
{
    pr::println("Hello, {}. You're number is {}. You are human: {}."_S,
        "there"_S, 42, true);

    return 0;
}
