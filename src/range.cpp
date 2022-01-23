#include <primer/range.h>

#include <stdint.h>

#include <primer/core/range.h>

namespace pr {

// int8_t
template<>
Range<int8_t>::Range(int8_t start, int8_t end)
{
    this->range = pr_range_new_i8(start, end);
}

// uint8_t
template<>
Range<uint8_t>::Range(uint8_t start, uint8_t end)
{
    this->range = pr_range_new_u8(start, end);
}

// int16_t
template<>
Range<int16_t>::Range(int16_t start, int16_t end)
{
    this->range = pr_range_new_i16(start, end);
}

// uint16_t
template<>
Range<uint16_t>::Range(uint16_t start, uint16_t end)
{
    this->range = pr_range_new_u16(start, end);
}

template <typename T>
Range<T>::~Range()
{
    pr_range_free(this->range);
}

} // namespace pr
