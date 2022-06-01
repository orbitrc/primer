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

    /// Append a value to the last of Vector.
    void push(const T& value)
    {
        this->_vec.push_back(value);
    }

    /// Inserts a value to the index.
    void insert(uint64_t index, T value)
    {
        this->_vec.insert(index, value);
    }

    /// Find first index of given value.
    /// Returns index if contanis value, or std::nullopt.
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

    /// Maps each elements and returns new Vector.
    Vector<T> map(std::function<T(const T&)> map_func) const
    {
        Vector<T> ret;

        for (auto& val: this->_vec) {
            ret.push(map_func(val));
        }

        return ret;
    }

    std::optional<T&> find(std::function<bool(const T&)>)
    {
        return std::nullopt;
    }

    //=======================
    // Range-based For Loop
    //=======================
    typename std::vector<T>::iterator begin()
    {
        return this->_vec.begin();
    }

    typename std::vector<T>::iterator end()
    {
        return this->_vec.end();
    }

    const typename std::vector<T>::const_iterator begin() const
    {
        return this->_vec.begin();
    }

    const typename std::vector<T>::const_iterator end() const
    {
        return this->_vec.end();
    }

    const typename std::vector<T>::const_iterator cbegin() const
    {
        return this->_vec.cbegin();
    }

    const typename std::vector<T>::const_iterator cend() const
    {
        return this->_vec.cend();
    }

    //==============
    // Operators
    //==============

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
