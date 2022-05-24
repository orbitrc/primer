#include "vector.h"

#include <assert.h>
#include <stdint.h>

#include <primer/vector.h>

namespace tests {

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

} // namespace tests
