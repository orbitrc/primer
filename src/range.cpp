#include <primer/range.h>

#include <stdint.h>

#include <primer/core/range.h>

namespace pr {

class RangeImpl
{
public:
    pr_range range;
};

//================
// Constructor
//================

// int8_t
template<>
Range<int8_t>::Range(int8_t start, int8_t end, bool exclusive)
{
    this->_impl = new RangeImpl{pr_range_new(start, end, exclusive)};
}

// uint8_t
template<>
Range<uint8_t>::Range(uint8_t start, uint8_t end, bool exclusive)
{
    this->_impl = new RangeImpl{pr_range_new(start, end, exclusive)};
}

// int16_t
template<>
Range<int16_t>::Range(int16_t start, int16_t end, bool exclusive)
{
    this->_impl = new RangeImpl{pr_range_new(start, end, exclusive)};
}

// uint16_t
template<>
Range<uint16_t>::Range(uint16_t start, uint16_t end, bool exclusive)
{
    this->_impl = new RangeImpl{pr_range_new(start, end, exclusive)};
}

// int32_t
template<>
Range<int32_t>::Range(int32_t start, int32_t end, bool exclusive)
{
    this->_impl = new RangeImpl{pr_range_new(start, end, exclusive)};
}

// uint32_t
template<>
Range<uint32_t>::Range(uint32_t start, uint32_t end, bool exclusive)
{
    this->_impl = new RangeImpl{pr_range_new(start, end, exclusive)};
}

// int64_t
template<>
Range<int64_t>::Range(int64_t start, int64_t end, bool exclusive)
{
    this->_impl = new RangeImpl{pr_range_new(start, end, exclusive)};
}

// uint64_t
template<>
Range<uint64_t>::Range(uint64_t start, uint64_t end, bool exclusive)
{
    this->_impl = new RangeImpl{pr_range_new(start, end, exclusive)};
}

//=====================
// Copy constructor
//=====================
template<>
Range<int8_t>::Range(const Range& other)
{
    this->_impl = new RangeImpl{other._impl->range};
}

template<>
Range<uint8_t>::Range(const Range& other)
{
    this->_impl = new RangeImpl{other._impl->range};
}

template<>
Range<int16_t>::Range(const Range& other)
{
    this->_impl = new RangeImpl{other._impl->range};
}

template<>
Range<uint16_t>::Range(const Range& other)
{
    this->_impl = new RangeImpl{other._impl->range};
}

template<>
Range<int32_t>::Range(const Range& other)
{
    this->_impl = new RangeImpl{other._impl->range};
}

template<>
Range<uint32_t>::Range(const Range& other)
{
    this->_impl = new RangeImpl{other._impl->range};
}

template<>
Range<int64_t>::Range(const Range& other)
{
    this->_impl = new RangeImpl{other._impl->range};
}

template<>
Range<uint64_t>::Range(const Range& other)
{
    this->_impl = new RangeImpl{other._impl->range};
}

//==============
// Destructor
//==============

// int8_t
template<>
Range<int8_t>::~Range()
{
    pr_range_free(this->_impl->range);
    delete this->_impl;
}

// uint8_t
template<>
Range<uint8_t>::~Range()
{
    pr_range_free(this->_impl->range);
    delete this->_impl;
}

// int16_t
template<>
Range<int16_t>::~Range()
{
    pr_range_free(this->_impl->range);
    delete this->_impl;
}

// uint16_t
template<>
Range<uint16_t>::~Range()
{
    pr_range_free(this->_impl->range);
    delete this->_impl;
}

// int32_t
template<>
Range<int32_t>::~Range()
{
    pr_range_free(this->_impl->range);
    delete this->_impl;
}

// uint32_t
template<>
Range<uint32_t>::~Range()
{
    pr_range_free(this->_impl->range);
    delete this->_impl;
}

// int64_t
template<>
Range<int64_t>::~Range()
{
    pr_range_free(this->_impl->range);
    delete this->_impl;
}

// uint64_t
template<>
Range<uint64_t>::~Range()
{
    pr_range_free(this->_impl->range);
    delete this->_impl;
}

//==============
// Contains
//==============

// int8_t
template<>
bool Range<int8_t>::contains(const int8_t value) const
{
    return pr_range_contains(this->_impl->range, value);
}

// uint8_t
template<>
bool Range<uint8_t>::contains(const uint8_t value) const
{
    return pr_range_contains(this->_impl->range, value);
}

// int16_t
template<>
bool Range<int16_t>::contains(const int16_t value) const
{
    return pr_range_contains(this->_impl->range, value);
}

// uint16_t
template<>
bool Range<uint16_t>::contains(const uint16_t value) const
{
    return pr_range_contains(this->_impl->range, value);
}

// int32_t
template<>
bool Range<int32_t>::contains(const int32_t value) const
{
    return pr_range_contains(this->_impl->range, value);
}

// uint32_t
template<>
bool Range<uint32_t>::contains(const uint32_t value) const
{
    return pr_range_contains(this->_impl->range, value);
}

// int64_t
template<>
bool Range<int64_t>::contains(const int64_t value) const
{
    return pr_range_contains(this->_impl->range, value);
}

// uint64_t
template<>
bool Range<uint64_t>::contains(const uint64_t value) const
{
    return pr_range_contains(this->_impl->range, value);
}

//==============
// Random
//==============

// int8_t
template<>
int8_t Range<int8_t>::random() const
{
    return pr_range_random(this->_impl->range);
}

// uint8_t
template<>
uint8_t Range<uint8_t>::random() const
{
    return pr_range_random_u(this->_impl->range);
}

// int16_t
template<>
int16_t Range<int16_t>::random() const
{
    return pr_range_random(this->_impl->range);
}

// uint16_t
template<>
uint16_t Range<uint16_t>::random() const
{
    return pr_range_random_u(this->_impl->range);
}

// int32_t
template<>
int32_t Range<int32_t>::random() const
{
    return pr_range_random(this->_impl->range);
}

// uint32_t
template<>
uint32_t Range<uint32_t>::random() const
{
    return pr_range_random_u(this->_impl->range);
}

// int64_t
template<>
int64_t Range<int64_t>::random() const
{
    return pr_range_random(this->_impl->range);
}

// uint64_t
template<>
uint64_t Range<uint64_t>::random() const
{
    return pr_range_random_u(this->_impl->range);
}

} // namespace pr
