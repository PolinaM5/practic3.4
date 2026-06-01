#include "HashTable.h"
#include <cstdint>
#include <string>
#include <functional>

HashTable::HashTable(size_t size) noexcept
    : _capacity(static_cast<int32_t>(size > 0 ? size : 100))
    , _filled(0)
    , table(_capacity)
{
}

HashTable::~HashTable() = default;

size_t HashTable::hash_function(const KeyType &key) const {
    std::hash<std::string> hasher;
    return hasher(key) % _capacity;
}

void HashTable::insert(const KeyType &key, const ValueType &value) {
    double load = static_cast<double>(_filled) / _capacity;
    if (load >= 0.75) {
        int32_t new_capacity = _capacity * 2;
        std::vector<std::list<std::pair<KeyType, ValueType>>> new_table(new_capacity);
        
        for (int32_t i = 0; i < _capacity; ++i) {
            for (auto& pair : table[i]) {
                std::hash<std::string> hasher;
                size_t new_index = hasher(pair.first) % new_capacity;
                new_table[new_index].push_back(std::move(pair));
            }
        }
        
        table = std::move(new_table);
        _capacity = new_capacity;
    }
    
    size_t index = hash_function(key);
    
    for (auto& pair : table[index]) {
        if (pair.first == key) {
            pair.second = value;
            return;
        }
    }
    
    table[index].emplace_back(key, value);
    ++_filled;
}

bool HashTable::find(const KeyType &key, ValueType &value) const {
    size_t index = hash_function(key);
    
    for (const auto& pair : table[index]) {
        if (pair.first == key) {
            value = pair.second;
            return true;
        }
    }
    
    return false;
}

void HashTable::remove(const KeyType &key) {
    size_t index = hash_function(key);
    auto& bucket = table[index];
    
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->first == key) {
            bucket.erase(it);
            --_filled;
            return;
        }
    }
}

ValueType& HashTable::operator[](const KeyType &key) {
    size_t index = hash_function(key);
    
    for (auto& pair : table[index]) {
        if (pair.first == key) {
            return pair.second;
        }
    }
    
    
    table[index].emplace_back(key, 0.0);
    ++_filled;
    
    
    return table[index].back().second;
}

double HashTable::getLoadFactor() {
    return static_cast<double>(_filled) / _capacity;
}
