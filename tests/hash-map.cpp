#include "hash-map.h"

#include <assert.h>
#include <stdint.h>

#include <primer/hash-map.h>

namespace tests {

void hash_map_length()
{
    pr::HashMap<int, int> map;

    map[5] = 500;
    map[6] = 600;

    assert(map.length() == 2);
}

void hash_map_insert()
{
    pr::HashMap<int, double> map;

    map.insert(3, 3.141592);

    assert(map[3] == 3.141592);
}

void hash_map_get()
{
    pr::HashMap<int, int> map;

    map[42] = 99999;

    auto opt = map.get(42);

    assert(opt != std::nullopt);

    opt.value().get() = 666;

    assert(map[42] == 666);
}

} // namespace tests
