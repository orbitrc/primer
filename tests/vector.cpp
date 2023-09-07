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
    // Make same type vector.
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

    // Make different type vector.
    auto v3 = v.map<double>([](auto& el) {
        return static_cast<double>(el);
    });

    assert(v3[0] == 1.0);
    assert(v3[1] == 2.0);
    assert(v3[2] == 3.0);
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
    pr::Vector<int32_t> v = {1, 2, 100};

    auto found = v.find([](int32_t two) {
        if (two == 2) {
            return true;
        }
        return false;
    });
    found->get() = 42;

    assert(v[1] == 42);
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

    pr::Vector<const char*> v2;

    v2.push("B1");
    v2.push("A1");
    v2.push("B2");
    v2.push("A2");

    v2.sort([](const char* const& a, const char* const& b) {
        return a[0] < b[0];
    });

    assert(v2[0][1] == '1');
    assert(v2[1][1] == '2');
}

void vector_c_ptr()
{
    pr::Vector<int32_t> v = {1, 1, 2, 3, 5, 8, 13};
    auto length = v.length();
    int32_t *ptr = v.c_ptr();

    for (uint64_t i = 0; i < length; ++i) {
        assert(ptr[i] == v[i]);
    }
}

} // namespace tests
