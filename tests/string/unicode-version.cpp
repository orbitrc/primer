#include <primer/string.h>

int main(int argc, char *argv[])
{
    if (pr::Unicode::version() != "15.0.0") {
        return 1;
    }

    return 0;
}

