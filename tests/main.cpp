#include <iostream>

#include "range.h"
#include "string.h"
#include "vector.h"
#include "json.h"

void test_log_start(const char *fn)
{
    std::cout << "[RUNNING] " << fn << std::endl;
}

void test_log_done(const char *fn)
{
    std::cout << "[DONE] " << fn << std::endl;
}

int main(int argc, char *argv[])
{
    //==========
    // Range
    //==========
    test_log_start("range_contains");
    tests::range_contains();
    test_log_done("range_contains");

    test_log_start("range_random");
    tests::range_random();
    test_log_done("range_random");

    //==========
    // String
    //==========
    test_log_start("string_contains");
    tests::string_contains();
    test_log_done("string_contains");

    test_log_start("string_compare");
    tests::string_compare();
    test_log_done("string_compare");

    // tests::string_starts_with();

    // tests::string_ends_with();

    test_log_start("string_trim");
    tests::string_trim();
    test_log_done("string_trim");

    test_log_start("string_split");
    tests::string_split();
    test_log_done("string_split");

    test_log_start("string_c_str");
    tests::string_c_str();
    test_log_done("string_c_str");

    test_log_start("unicode_na");
    tests::unicode_na();
    test_log_done("unicode_na");

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
