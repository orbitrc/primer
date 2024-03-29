#include <iostream>

#include "range.h"
#include "string.h"
#include "vector.h"
#include "json.h"
#include "format.h"
#include "hash-map.h"
#include "byte-array.h"
#include "d-bus.h"

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
    test_with_log("range_getters", tests::range_getters);

    test_with_log("range_contains", tests::range_contains);

    test_with_log("range_random", tests::range_random);

    test_with_log("range_copy", tests::range_copy);

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

    test_with_log("string_unicode_scalars", tests::string_unicode_scalars);

    test_with_log("unicode_scalar_compare", tests::unicode_scalar_compare);

    test_with_log("unicode_scalar_literal", tests::unicode_scalar_literal);

    test_with_log("unicode_na", tests::unicode_na);

    test_with_log("unicode_encoder_utf8", tests::unicode_encoder_utf8);

    test_with_log("unicode_encoder_utf16", tests::unicode_encoder_utf16);

    test_with_log("unicode_decoder_utf8", tests::unicode_decoder_utf8);

    test_with_log("unicode_decoder_utf16", tests::unicode_decoder_utf16);

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

    test_with_log("vector_sort", tests::vector_sort);

    test_with_log("vector_c_ptr", tests::vector_c_ptr);

    //==========
    // JSON
    //==========
    test_with_log("json_array", tests::json_array);

    //==========
    // Format
    //==========
    test_with_log("format_format", tests::format);

    //==========
    // HashMap
    //==========
    test_with_log("hash_map_length", tests::hash_map_length);

    test_with_log("hash_map_insert", tests::hash_map_insert);

    test_with_log("hash_map_get", tests::hash_map_get);

    //============
    // ByteArray
    //============
    test_with_log("byte_array_init", tests::byte_array_init);

    test_with_log("byte_array_equal", tests::byte_array_equal);

    test_with_log("byte_array_subset", tests::byte_array_subset);

    //=========
    // DBus
    //=========
    test_with_log("d_bus_argument", tests::d_bus_argument);

    test_with_log("d_bus_dict_entry", tests::d_bus_dict_entry);

    return 0;
}
