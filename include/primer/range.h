#ifndef _PRIMER_RANGE_H
#define _PRIMER_RANGE_H

#include <stdint.h>

#include <primer/core/range.h>

namespace pr {

template <typename T>
class Range {
private:
    pr_range range;
public:
    //=========================
    // Constructor/Destructor
    //=========================

    Range<T>(T start, T end);

    ~Range();

    //=========================
    // Element access
    //=========================

    T start() const;

    T end() const;
};

} // namespace pr

#endif // _PRIMER_RANGE_H
