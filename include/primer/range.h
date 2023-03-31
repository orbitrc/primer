#ifndef _PRIMER_RANGE_H
#define _PRIMER_RANGE_H

#include <stdint.h>

namespace pr {

class RangeImpl;

template <typename T>
class Range {
private:
    RangeImpl *_impl;

public:
    //=========================
    // Constructor/Destructor
    //=========================

    Range<T>(T start, T end, bool exclusive=true);

    Range<T>(const Range& other);

    ~Range();

    //=========================
    // Element access
    //=========================

    T start() const
    {
        return this->range.start;
    }

    T end() const
    {
        return this->range.end;
    }

    bool exclusive() const
    {
        return this->range.exclusive;
    }

    //=========================
    // Others
    //=========================

    bool contains(const T value) const;

    T random() const;
};

} // namespace pr

#endif // _PRIMER_RANGE_H
