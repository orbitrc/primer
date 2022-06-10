#include "vector.h"

#include <assert.h>
#include <stdint.h>

#include <primer/vector.h>

namespace tests {

void vector_length()
{
    pr::Vector<int32_t> v;

    assert(v.length() == 0);

    v.push(10);
    v.push(20);
    v.push(30);

    assert(v.length() == 3);
}

void vector_map()
{
    pr::Vector<int32_t> v;

    v.push(1);
    v.push(2);
    v.push(3);

    auto v2 = v.map([](auto& el) {
        return el * 2;
    });

    assert(v2[0] == 2);
    assert(v2[1] == 4);
    assert(v2[2] == 6);
}

void vector_loop()
{
    pr::Vector<int32_t> v;

    v.push(10);
    v.push(10);
    v.push(10);

    for (auto& val: v) {
        assert(val == 10);
    }
}

void vector_find()
{
    pr::Vector<int32_t> v;

    v.push(1);
    v.push(2);
    v.push(100);
}

void vector_index()
{
    pr::Vector<int32_t> v;

    v.push(1);
    v.push(2);
    v.push(4);

    auto index = v.index(4);

    assert(index == 2);
}

} // namespace tests
