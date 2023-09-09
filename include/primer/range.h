#ifndef _PRIMER_RANGE_H
#define _PRIMER_RANGE_H

#include <stdint.h>

namespace pr {

class RangeImpl;

class String;

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

    T start() const;

    T end() const;

    bool exclusive() const;

    //=========================
    // Others
    //=========================

    bool contains(const T value) const;

    T random() const;

    /// Create a new String that represents the Range object.
    ///
    /// \since 4.0
    String to_string() const;
};

} // namespace pr

#endif // _PRIMER_RANGE_H
