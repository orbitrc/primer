#ifndef _PRIMER_RANGE_H
#define _PRIMER_RANGE_H

#include <stdint.h>

typedef struct pr_range pr_range;

namespace pr {

template <typename T>
class Range {
private:
    pr_range *range;
public:
    //=========================
    // Constructor/Destructor
    //=========================

    Range<T>(T start, T end);

    ~Range();
};

} // namespace pr

#endif // _PRIMER_RANGE_H
