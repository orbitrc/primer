#include <primer/range.h>

#include <stdint.h>

#include <primer/core/range.h>

namespace pr {

//================
// Constructor
//================

// int8_t
template<>
Range<int8_t>::Range(int8_t start, int8_t end, bool exclusive)
{
    this->range = pr_range_new(start, end, exclusive);
}

// uint8_t
template<>
Range<uint8_t>::Range(uint8_t start, uint8_t end, bool exclusive)
{
    this->range = pr_range_new(start, end, exclusive);
}

// int16_t
template<>
Range<int16_t>::Range(int16_t start, int16_t end, bool exclusive)
{
    this->range = pr_range_new(start, end, exclusive);
}

// uint16_t
template<>
Range<uint16_t>::Range(uint16_t start, uint16_t end, bool exclusive)
{
    this->range = pr_range_new(start, end, exclusive);
}

// int32_t
template<>
Range<int32_t>::Range(int32_t start, int32_t end, bool exclusive)
{
    this->range = pr_range_new(start, end, exclusive);
}

// uint32_t
template<>
Range<uint32_t>::Range(uint32_t start, uint32_t end, bool exclusive)
{
    this->range = pr_range_new(start, end, exclusive);
}

// int64_t
template<>
Range<int64_t>::Range(int64_t start, int64_t end, bool exclusive)
{
    this->range = pr_range_new(start, end, exclusive);
}

// uint64_t
template<>
Range<uint64_t>::Range(uint64_t start, uint64_t end, bool exclusive)
{
    this->range = pr_range_new(start, end, exclusive);
}

//==============
// Destructor
//==============

// int8_t
template<>
Range<int8_t>::~Range()
{
    pr_range_free(this->range);
}

// uint8_t
template<>
Range<uint8_t>::~Range()
{
    pr_range_free(this->range);
}

// int16_t
template<>
Range<int16_t>::~Range()
{
    pr_range_free(this->range);
}

// uint16_t
template<>
Range<uint16_t>::~Range()
{
    pr_range_free(this->range);
}

// int32_t
template<>
Range<int32_t>::~Range()
{
    pr_range_free(this->range);
}

// uint32_t
template<>
Range<uint32_t>::~Range()
{
    pr_range_free(this->range);
}

// int64_t
template<>
Range<int64_t>::~Range()
{
    pr_range_free(this->range);
}

// uint64_t
template<>
Range<uint64_t>::~Range()
{
    pr_range_free(this->range);
}

//==============
// Random
//==============

// int8_t
template<>
int8_t Range<int8_t>::random() const
{
    return pr_range_random(this->range);
}

// uint8_t
template<>
uint8_t Range<uint8_t>::random() const
{
    return pr_range_random_u(this->range);
}

// int16_t
template<>
int16_t Range<int16_t>::random() const
{
    return pr_range_random(this->range);
}

// uint16_t
template<>
uint16_t Range<uint16_t>::random() const
{
    return pr_range_random_u(this->range);
}

// int32_t
template<>
int32_t Range<int32_t>::random() const
{
    return pr_range_random(this->range);
}

// uint32_t
template<>
uint32_t Range<uint32_t>::random() const
{
    return pr_range_random_u(this->range);
}

// int64_t
template<>
int64_t Range<int64_t>::random() const
{
    return pr_range_random(this->range);
}

// uint64_t
template<>
uint64_t Range<uint64_t>::random() const
{
    return pr_range_random_u(this->range);
}

} // namespace pr
