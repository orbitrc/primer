#ifndef _PRIMER_BYTE_ARRAY_H
#define _PRIMER_BYTE_ARRAY_H

#include <stdint.h>

#include <memory>
#include <vector>
#include <initializer_list>

#include <primer/range.h>
#include <primer/decl/string.h>

namespace pr {

/// \brief A `ByteArray` class represents an abstraction of an array of 8-bit
/// data type.
///
/// \since 0.5
class ByteArray
{
public:
    /// \brief Default constructor.
    ByteArray();

    /// \brief Construct a `ByteArray` with the given length.
    ByteArray(uint64_t length);

    /// \brief Construct a `ByteArray` with C-style raw pointer with length.
    ///
    /// \param data A valid C pointer.
    /// \param length The length of the data.
    ByteArray(const uint8_t *data, uint64_t length);

    /// \brief Construct a `ByteArray` with C-style raw pointer with length.
    ///
    /// \param data A valid C pointer.
    /// \param length The length of the data.
    ///
    /// Because most of the C APIs using `const char*` as a byte data. This is
    /// a convenience overloading for those.
    ByteArray(const char *data, uint64_t length);

    /// \brief Construct a `ByteArray` with `std::initializer_list`.
    ///
    /// \param list The initializer list.
    ByteArray(std::initializer_list<uint8_t> list);

    /// \brief Copy constructor for `ByteArray`.
    ByteArray(const ByteArray& other);

    /// \brief Get the fixed length of this array.
    uint64_t length() const;

    /// \brief Set the length of this array.
    ///
    /// \param length The length.
    ///
    /// If the length is smaller than the current length, then the data will
    /// be discarded from last.
    /// If the length is larger than the current length, then the remains will
    /// be filled with value zero.
    void set_length(uint64_t length);

    uint8_t& operator[](uint64_t index);

    uint8_t& operator[](uint64_t index) const;

    /// Get a subset of this array.
    ByteArray operator[](const Range<uint64_t>& range) const;

    bool operator==(const ByteArray& other) const;

    bool operator!=(const ByteArray& other) const;

    uint8_t* c_ptr();

    const uint8_t* c_ptr() const;

    String to_string() const;

private:
    std::shared_ptr<std::vector<uint8_t>> _vec;
    uint64_t _length;
    uint64_t _offset;
};

} // namespace pr

#endif // _PRIMER_BYTE_ARRAY_H
