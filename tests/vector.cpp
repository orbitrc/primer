#include "vector.h"

#include <assert.h>
#include <stdint.h>

#include <primer/vector.h>

namespace tests {

void vector_initializer_list()
{
    pr::Vector<int32_t> v{10, 20, 30, 40};

    assert(v[0] == 10);
    assert(v[1] == 20);
    assert(v[2] == 30);
    assert(v[3] == 40);
}

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

void vector_insert()
{
    pr::Vector<int32_t> v;

    v.push(2);
    v.push(3);
    v.insert(0, 1);

    assert(v[0] == 1);
}

void vector_remove()
{
    pr::Vector<int32_t> v;

    v.push(1);
    v.push(2);
    v.push(3);

    auto removed = v.remove(1);
    (void)removed;

    assert(v.length() == 2);

    assert(removed = 2);

    assert(v[0] == 1);
    assert(v[1] == 3);
}

void vector_sort()
{
    pr::Vector<int32_t> v;

    v.push(5);
    v.push(1);
    v.push(4);
    v.push(2);
    v.push(3);

    v.sort();

    assert(v[0] == 1);
    assert(v[1] == 2);
    assert(v[2] == 3);
    assert(v[3] == 4);
    assert(v[4] == 5);
}

} // namespace tests
