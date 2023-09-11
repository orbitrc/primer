#include "byte-array.h"

#include <assert.h>

#include <primer/byte-array.h>
#include <primer/range.h>

namespace tests {

void byte_array_init()
{
    pr::ByteArray ba(11);

    assert(ba.length() == 11);

    uint8_t *data = ba.c_ptr();
    for (uint64_t i = 0; i < ba.length(); ++i) {
        assert(data[i] == 0x00);
    }
}

void byte_array_equal()
{
    pr::ByteArray arr1 = {0x01, 0x02, 0x03};
    pr::ByteArray arr2 = {0x00, 0x02, 0x03};

    assert(arr1 != arr2);

    arr2[0] = 0x01;

    assert(arr1 == arr2);
}

void byte_array_subset()
{
    // Get a subset and check the elements.
    pr::ByteArray arr1 = {'H', 'e', 'l', 'l', 'o'};
    pr::ByteArray arr_sub = arr1[pr::Range<uint64_t>(2, 3, false)];

    assert(arr_sub[0] == 'l');
    assert(arr_sub[1] == 'l');

    // Set length.
    assert(arr_sub.length() == 2);

    pr::ByteArray arr_cmp = {'l', 'l', 0x00};

    arr_sub.set_length(3);
    assert(arr_sub.length() == 3);
    {
        assert(arr_sub[0] == 'l');
        assert(arr_sub[1] == 'l');
        assert(arr_sub[2] == 0x00);
    }

    assert(arr_sub == arr_cmp);
}

} // namespace tests
