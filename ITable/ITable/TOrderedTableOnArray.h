#ifndef TOrderedTableOnArray_H
#define TOrderedTableOnArray_H

#include "ITable.h"
#include "TPair.h"
#include <iostream>
#include "TOrderedArray.h"

template <typename TKey, typename TData>
class TOrderedTableOnArray : public ITable<TKey, TData> {
    OrderedArray<TPair<TKey, TData>> data;
public:
    void add(const TKey& key_, const TData& data_) {
        for (auto i = data.begin(); i != data.end(); i++) {
            if (i->getFirst() == key_) {
                throw std::logic_error("Key already exists");
            }
        }
        data.add(TPair<TKey, TData>(key_, data_));
    }
    void remove(const TKey& key_) {
        for (auto i = data.begin(); i != data.end(); i++) {
            if (i->getFirst() == key_) {
                data.remove(i);
                return;
            }
        }
    }
    TData get(const TKey& key_) {
        for (auto i = data.begin(); i != data.end(); i++) {
            if (i->getFirst() == key_) {
                return i->getSecond();
            }
        }
    }
    void clear() {
        data.clear();
    }
    size_t size() {
        return data.getSize();
    }
    bool isEmpty() {
        return data.isEmpty();
    }

    class iterator {
    private:
        typename OrderedArray<TPair<TKey, TData>>::iterator iter;

    public:
        iterator(typename OrderedArray<TPair<TKey, TData>>::iterator it) : iter(it) {}

        iterator& operator++() {
            ++iter;
            return *this;
        }

        TPair<TKey, TData>& operator*() {
            return *iter;
        }

        bool operator!=(const iterator& other) const {
            return iter != other.iter;
        }
    };

    class const_iterator {
    private:
        typename OrderedArray<TPair<TKey, TData>>::const_iterator iter;

    public:
        const_iterator(typename OrderedArray<TPair<TKey, TData>>::const_iterator it) : iter(it) {}

        const_iterator& operator++() {
            ++iter;
            return *this;
        }

        const TPair<TKey, TData>& operator*() const {
            return *iter;
        }

        bool operator!=(const const_iterator& other) const {
            return iter != other.iter;
        }
    };

    iterator begin() {
        return iterator(data.begin());
    }

    iterator end() {
        return iterator(data.end());
    }

    const_iterator begin() const {
        return const_iterator(data.begin());
    }

    const_iterator end() const {
        return const_iterator(data.end());
    }

};
#endif