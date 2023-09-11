#include <primer/byte-array.h>

#include <string.h>

#include <iomanip>

namespace pr {

ByteArray::ByteArray()
{
    this->_length = 0;
    this->_offset = 0;
}

ByteArray::ByteArray(uint64_t length)
{
    this->_length = length;
    this->_offset = 0;
    this->_vec = std::make_shared<std::vector<uint8_t>>();

    this->_vec->resize(length);
    this->_vec->assign(length, 0);
}

ByteArray::ByteArray(const uint8_t *data, uint64_t length)
{
    this->_length = length;
    this->_offset = 0;
    this->_vec = std::make_shared<std::vector<uint8_t>>();

    this->_vec->assign(data, data + length);
}

ByteArray::ByteArray(const char *data, uint64_t length)
{
    this->_length = length;
    this->_offset = 0;
    this->_vec = std::make_shared<std::vector<uint8_t>>();

    this->_vec->assign(data, data + length);
}

ByteArray::ByteArray(std::initializer_list<uint8_t> list)
{
    this->_vec = std::make_shared<std::vector<uint8_t>>(
        std::vector<uint8_t>(list));

    this->_length = this->_vec->size();
    this->_offset = 0;
}

ByteArray::ByteArray(const ByteArray& other)
{
    this->_length = other._length;
    this->_offset = other._offset;

    // Not actual copy. Just copy the pointer.
    this->_vec = other._vec;
}

uint64_t ByteArray::length() const
{
    return this->_length;
}

void ByteArray::set_length(uint64_t length)
{
    if (this->_offset == 0) {
        if (length < this->_length) {
            this->_length = length;
            return;
        } else if (length == this->_length) {
            // Do nothing.
            return;
        } else if (length > this->_length) {
            this->_length = length;
            if (this->_vec.unique()) {
                this->_vec->resize(length);
            } else {
                // Copy on write.
                auto src = this->_vec;
                this->_vec = std::make_shared<std::vector<uint8_t>>();
                this->_vec->assign(src->begin(), src->end());
            }
            return;
        }
    } else {
        if (length == this->_length) {
            return;
        }
        // Copy on write.
        auto src = this->_vec;
        this->_vec = std::make_shared<std::vector<uint8_t>>();
        this->_vec->assign(src->begin() + this->_offset,
            src->end() - this->_offset + 1);
        this->_vec->resize(length);
        // Update infos.
        this->_length = length;
        this->_offset = 0;

        return;
    }
}

uint8_t& ByteArray::operator[](uint64_t index)
{
    return (*this->_vec)[index + this->_offset];
}

uint8_t& ByteArray::operator[](uint64_t index) const
{
    return (*this->_vec)[index + this->_offset];
}

ByteArray ByteArray::operator[](const Range<uint64_t>& range) const
{
    uint64_t count = range.exclusive()
        ? range.end() - range.start()
        : range.end() - range.start() + 1;
    ByteArray arr;
    arr._vec = this->_vec;
    arr._length = count;
    arr._offset = range.start();

    return arr;
}

bool ByteArray::operator==(const ByteArray& other) const
{
    if (this->_length != other._length) {
        return false;
    }

    int result = memcmp(this->_vec->data() + this->_offset,
        other._vec->data() + other._offset,
        this->_length);

    return result == 0;
}

bool ByteArray::operator!=(const ByteArray& other) const
{
    return !(*this == other);
}

uint8_t* ByteArray::c_ptr()
{
    return this->_vec->data();
}

const uint8_t* ByteArray::c_ptr() const
{
    return this->_vec->data();
}

String ByteArray::to_string() const
{
    std::ostringstream oss;
    oss << std::uppercase;
    oss << '[';
    for (uint64_t i = 0; i < this->_length; ++i) {
        oss << "0x" << std::hex << std::setw(2) << std::setfill('0')
            << (int32_t)*(this->_vec->data() + this->_offset + i);
        if (i < this->_length - 1) {
            oss << ", ";
        }
    }
    oss << "]";
    std::string s = oss.str();

    return String(s.c_str());
}

} // namespace pr
