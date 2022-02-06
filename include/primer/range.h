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

    Range<T>(T start, T end, bool exclusive=true);

    ~Range()
    {
        pr_range_free(this->range);
    }

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

    bool contains(const T value) const
    {
        return pr_range_contains(this->range, static_cast<int64_t>(value));
    }

    T random() const;
};

} // namespace pr

#endif // _PRIMER_RANGE_H
