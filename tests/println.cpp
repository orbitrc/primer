#include <primer/io.h>
#include <primer/range.h>

int main(int argc, char *argv[])
{
    pr::println("Hello, {}. You're number is {}. You are human: {}."_S,
        "there"_S, 42, true);

    pr::Range rng(0, 10, false);
    pr::println("{}", rng);

    pr::Vector<int> iv;
    iv.push(100);
    iv.push(42);
    iv.push(500);
    pr::println("{}", iv);

    pr::Vector<pr::String> sv;
    sv.push("One"_S);
    sv.push("Two"_S);
    sv.push("Three"_S);
    sv.push("Four"_S);
    pr::println("{}", sv);

    // to_string() test.
    pr::Vector<pr::Range<int32_t>> rv;
    rv.push(pr::Range(0, 10, false));
    rv.push(pr::Range(10, 42));
    pr::println("{}", rv);

    return 0;
}
