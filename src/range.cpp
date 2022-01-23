#include <primer/range.h>

#include <stdint.h>

#include <primer/core/range.h>

namespace pr {

template<>
Range<int8_t>::Range(int8_t start, int8_t end)
{
    this->range = pr_range_new_i8(start, end);
}

template<>
Range<uint8_t>::Range(uint8_t start, uint8_t end)
{
    this->range = pr_range_new_u8(start, end);
}

template <typename T>
Range<T>::~Range()
{
    pr_range_free(this->range);
}

} // namespace pr
