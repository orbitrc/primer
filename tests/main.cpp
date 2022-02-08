#include "range.h"
#include "json.h"

int main(int argc, char *argv[])
{
    //==========
    // Range
    //==========
    tests::range_contains();

    tests::range_random();

    //==========
    // JSON
    //==========
    tests::json_array();

    return 0;
}
