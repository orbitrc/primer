#include "d-bus.h"

#include <assert.h>

#include <primer/d-bus.h>

namespace tests {

void d_bus_argument()
{
    pr::DBusArgument(42);
}

void d_bus_dict_entry()
{
    auto d = pr::DBusDictEntry();
    d.set_key_type(pr::DBus::Type::String);
    assert(d.key_type() == pr::DBus::Type::String);
}

} // namespace tests
