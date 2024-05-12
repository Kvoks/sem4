#ifndef TTableOnArray_H
#define TTableOnArray_H

#include "ITable.h"
#include "TPair.h"
#include <iostream>
#include <vector>

template <typename TKey, typename TData>
class TTableOnArray : public ITable<TKey, TData> {
    std::vector<TPair<TKey, TData>> data;
public:
    void add(const TKey& key_, const TData& data_) {
        if (get(key_) == NULL) {
            data.push_back(TPair<TKey, TData>(key_, data_));
        }
        else {
            throw std::logic_error("Key already exists");
        }

    }
    void remove(const TKey& key_) {
        for (int i = 0; i < data.size(); i++) {
            if (data[i].getFirst() == key_) {
                data.erase(data.begin() + i);
                return;
            }
        }
    }
    TData get(const TKey& key_) {
        for (int i = 0; i < data.size(); i++) {
            if (data[i].getFirst() == key_) {
                return data[i].getSecond();
            }
        }
        return NULL;
    }
    void clear() {
        data.clear();
    }
    size_t size() {
        return data.size();
    }
    bool isEmpty() {
        return data.empty();
    }

};
#endif