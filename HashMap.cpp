#include <iostream>
#include <list>
#include <stdexcept>
#include <utility>
#include <vector>

const size_t TABLE_SIZE = 49999;
const size_t MOD = 49991;

template<class KeyType, class ValueType, class Hash = std::hash<KeyType> >
class HashMap {
 private:
    std::list<std::pair<const KeyType, ValueType>> elements;
    std::vector<std::list<typename std::list<std::pair<const KeyType, ValueType>>::iterator>> table;
    Hash table_hasher;

 public:
    typedef typename std::list<std::pair<const KeyType, ValueType>>::iterator iterator;
    typedef typename std::list<std::pair<const KeyType, ValueType>>::const_iterator const_iterator;
    HashMap(Hash hasher = Hash()) : table(TABLE_SIZE), table_hasher(hasher) {}

    template<typename Iterator>
    HashMap(Iterator begin, Iterator end, Hash hasher = Hash()) : HashMap() {
        table_hasher = hasher;
        for (; begin != end; ++begin) {
            KeyType key = begin->first;
            size_t id = hasher(key) % MOD + 1;
            elements.push_back(*begin);
            iterator it = --elements.end();
            table[id].push_back(it);
        }
    }

    HashMap(const std::initializer_list<std::pair<KeyType, ValueType>>
            valuesList, Hash hasher = Hash()) :
            HashMap(valuesList.begin(), valuesList.end(), hasher) {}

    size_t size() const {
        return elements.size();
    }

    bool empty() const {
        return elements.empty();
    }

    Hash hash_function() const {
        return table_hasher;
    }

    ValueType& insert(const std::pair<KeyType, ValueType>& element) {
        KeyType key = element.first;
        size_t id = table_hasher(key) % MOD + 1;
        for (typename std::list<iterator>::iterator
                     it = table[id].begin(); it != table[id].end(); ++it) {
            if ((*it)->first == key) {
                return (*it)->second;
            }
        }
        elements.push_back(element);
        iterator it = --elements.end();
        table[id].push_back(it);
        return it->second;
    }

    void erase(const KeyType& key) {
        size_t id = table_hasher(key) % MOD + 1;
        bool have_it = false;
        typename std::list<iterator>::iterator del;
        for (typename std::list<iterator>::iterator
                     it = table[id].begin(); it != table[id].end(); ++it) {
            if ((*it)->first == key) {
                have_it = true;
                del = it;
                elements.erase(*it);
                break;
            }
        }
        if (have_it) {
            table[id].erase(del);
        }
    }

    iterator begin() {
        return elements.begin();
    }

    iterator end() {
        return elements.end();
    }

    const_iterator begin() const {
        return elements.cbegin();
    }

    const_iterator end() const {
        return elements.cend();
    }

    iterator find(const KeyType& key) {
        size_t id = table_hasher(key) % MOD + 1;
        for (typename std::list<iterator>::iterator
                     it = table[id].begin(); it != table[id].end(); ++it) {
            if ((*it)->first == key) {
                return *it;
            }
        }
        return end();
    }

    const_iterator find(const KeyType& key) const {
        const_iterator it;
        for (it = elements.begin(); it != elements.end(); ++it) {
            if ((it)->first == key)
                break;
        }
        return it;
    }

    ValueType& operator[](const KeyType& key) {
        return (insert(std::make_pair(key, ValueType())));
    }

    const ValueType& at(const KeyType& key) const {
        const_iterator it = find(key);
        if (it != end()) {
            return it->second;
        } else {
            throw std::out_of_range("Out of range");
        }
    }

    void clear() {
        for (iterator it = elements.begin(); it != end(); ++it) {
            KeyType key = it->first;
            size_t id = table_hasher(key) % MOD + 1;
            table[id].clear();
        }
        elements.clear();
    }

    HashMap<KeyType, ValueType>& operator =(const HashMap<KeyType, ValueType>& map) {
        if (this != &map) {
            table_hasher = map.table_hasher;
            clear();
            for (auto& elem : map.elements) {
                insert(elem);
            }
        }
        return *this;
    }
};
