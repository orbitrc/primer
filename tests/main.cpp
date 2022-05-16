#include "range.h"
#include "string.h"
#include "json.h"

int main(int argc, char *argv[])
{
    //==========
    // Range
    //==========
    tests::range_contains();

    tests::range_random();

    //==========
    // String
    //==========
    tests::string_contains();

    //==========
    // JSON
    //==========
    tests::json_array();

    return 0;
}
