#ifndef _PRIMER_HASH_MAP_H
#define _PRIMER_HASH_MAP_H

#include <stdint.h>

#include <unordered_map>
#include <optional>
#include <functional>

#include <primer/vector.h>

namespace pr {

template <typename K, typename V>
class HashMap
{
public:
    HashMap<K, V>()
    {
    }

    ~HashMap<K, V>()
    {
    }

    uint64_t length() const
    {
        return this->_map.size();
    }

    void insert(const K& key, const V& value)
    {
        this->_map.insert({key, value});
    }

    std::optional<std::reference_wrapper<V>> get(const K& key)
    {
        auto end = this->_map.end();
        for (auto it = this->_map.begin(); it != end; ++it) {
            if (it->first == key) {
                return it->second;
            }
        }

        return std::nullopt;
    }

    Vector<K> keys() const
    {
        Vector<K> v;

        auto end = this->_map.end();
        for (auto it = this->_map.begin(); it != end; ++it) {
            v.push(it->first);
        }

        return v;
    }

    //===============
    // Operators
    //===============

    V& operator[](const K& key)
    {
        return this->_map[key];
    }

private:
    std::unordered_map<K, V> _map;
};

} // namespace pr

#endif /* _PRIMER_HASH_MAP_H */
