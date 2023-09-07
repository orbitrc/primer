#ifndef _PRIMER_VECTOR_H
#define _PRIMER_VECTOR_H

#include <stdint.h>

#include <vector>
#include <algorithm>
#include <optional>
#include <functional>
#include <initializer_list>

#include <primer/decl/string.h>
#include <primer/format.h>

namespace pr {

template <typename T>
class Vector
{
public:
    Vector<T>()
    {
    }

    Vector<T>(std::initializer_list<T> init)
    {
        this->_vec = init;
    }

    ~Vector<T>()
    {
    }

    /// Returns number of items in Vector.
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
        // Find iter.
        auto it = this->_vec.begin();
        it += index;

        this->_vec.insert(it, value);
    }

    /// Removes and returns the element of given index.
    T remove(uint64_t index)
    {
        auto it = this->_vec.begin();
        it += index;

        auto el = this->_vec[index];
        this->_vec.erase(it);

        return el;
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
            ++index;
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

    /// Map each elements and returns a new Vector contains given template type.
    ///
    /// \since 0.4
    template<typename U>
    Vector<U> map(std::function<U(const T&)> map_func) const
    {
        Vector<U> ret;

        for (auto& val: this->_vec) {
            ret.push(map_func(val));
        }

        return ret;
    }

    /// Find an object by the find function.
    ///
    /// \since 0.4
    std::optional<std::reference_wrapper<T>>
    find(std::function<bool(const T&)> find_func)
    {
        for (auto& val: this->_vec) {
            if (find_func(val) == true) {
                return val;
            }
        }

        return std::nullopt;
    }

    /// Sort items in the Vector. This method changes the Vector.
    /// Sort is in stable.
    void sort()
    {
        std::stable_sort(this->begin(), this->end());
    }

    /// Sort items in the Vector by given function.
    /// This method changes the Vector.
    /// Sort is in stable.
    void sort(std::function<bool(const T&, const T&)> func)
    {
        std::stable_sort(this->begin(), this->end(), func);
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

    //==============
    // Conversions
    //==============

    /// Vector to string representation.
    ///
    /// \since 0.4
    String to_string() const
    {
        String s = "["_S;

        auto length = this->length();
        for (uint64_t i = 0; i < length; ++i) {
            String f = format("{}", this->_vec[i]);
            if (i < length - 1) {
                s = s + f + ", ";
            } else {
                s = s + f;
            }
        }
        s = s + "]"_S;

        return s;
    }

    //===============
    // C Compatible
    //===============

    /// Returns the C pointer underlying the Vector.
    ///
    /// \since 0.4
    T* c_ptr()
    {
        return this->_vec.data();
    }

    /// Returns the C pointer underlying the Vector.
    ///
    /// \since 0.4
    const T* c_ptr() const
    {
        return this->_vec.data();
    }

private:
    std::vector<T> _vec;
};

/// Vector to string representation. Special for Vector of String.
///
/// \since 0.4
template<> inline
String Vector<String>::to_string() const
{
    String s = "["_S;

    auto length = this->length();
    for (uint64_t i = 0; i < length; ++i) {
        String f = format("\"{}\"", this->_vec[i]);
        if (i < length - 1) {
            s = s + f + ", ";
        } else {
            s = s + f;
        }
    }
    s = s + "]"_S;

    return s;
}

} // namespace pr

#endif // _PRIMER_VECTOR_H
