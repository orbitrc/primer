#include "range.h"
#include "string.h"
#include "vector.h"
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
    // Vector
    //==========
    tests::vector_map();

    //==========
    // JSON
    //==========
    tests::json_array();

    return 0;
}
