#include <iostream>

#include "range.h"
#include "string.h"
#include "vector.h"
#include "json.h"

void test_with_log(const char *name, void(*test_func)())
{
    std::cout << "[RUNNING] " << name << std::endl;
    test_func();
    std::cout << "[DONE]    " << name << std::endl;
}

int main(int argc, char *argv[])
{
    //==========
    // Range
    //==========
    test_with_log("range_contains", tests::range_contains);

    test_with_log("range_random", tests::range_random);

    //==========
    // String
    //==========
    test_with_log("string_contains", tests::string_contains);

    test_with_log("string_compare", tests::string_compare);

    test_with_log("string_starts_with", tests::string_starts_with);

    test_with_log("string_ends_with", tests::string_ends_with);

    test_with_log("string_trim", tests::string_trim);

    test_with_log("string_split", tests::string_split);

    test_with_log("string_c_str", tests::string_c_str);

    test_with_log("string_add", tests::string_add);

    test_with_log("unicode_na", tests::unicode_na);

    //==========
    // Vector
    //==========
    test_with_log("vector_initializer_list", tests::vector_initializer_list);

    test_with_log("vector_length", tests::vector_length);

    test_with_log("vector_map", tests::vector_map);

    test_with_log("vector_loop", tests::vector_loop);

    test_with_log("vector_index", tests::vector_index);

    test_with_log("vector_insert", tests::vector_insert);

    test_with_log("vector_remove", tests::vector_remove);

    //==========
    // JSON
    //==========
    test_with_log("json_array", tests::json_array);

    return 0;
}
