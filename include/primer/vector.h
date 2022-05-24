#ifndef _PRIMER_VECTOR_H
#define _PRIMER_VECTOR_H

#include <stdint.h>

#include <vector>
#include <optional>
#include <functional>

namespace pr {

template <typename T>
class Vector
{
public:
    Vector<T>()
    {
    }

    ~Vector<T>()
    {
    }

    uint64_t length() const
    {
        return this->_vec.size();
    }

    void push(const T& value)
    {
        this->_vec.push_back(value);
    }

    std::optional<uint64_t> index(const T& value) const
    {
        uint64_t index = 0;

        for (auto it = this->_vec.begin(); it != this->_vec.end(); ++it) {
            if (*it == value) {
                return std::optional<uint64_t>(index);
            }
        }

        return std::nullopt;
    }

    Vector<T> map(std::function<T(const T&)> map_func) const
    {
        Vector<T> ret;

        for (auto& val: this->_vec) {
            ret.push(map_func(val));
        }

        return ret;
    }

    T& operator[](uint64_t index)
    {
        return this->_vec[index];
    }

    const T& operator[](uint64_t index) const
    {
        return this->_vec[index];
    }

private:
    std::vector<T> _vec;
};

} // namespace pr

#endif // _PRIMER_VECTOR_H
