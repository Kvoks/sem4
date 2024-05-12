#ifndef TTableOnList_H
#define TTableOnList_H

#include "ITable.h"
#include "TPair.h"
#include <iostream>
#include <list>

template <typename TKey, typename TData>
class TTableOnList : public ITable<TKey, TData> {
    std::list<TKey, TData> data;
public:
    void add(const TKey& key, const TData& data) {
        data.push_back(TPair<TKey, TData>(key, data));
    }
    void remove(const TKey& key) {
        for (auto i = data.begin(); i != data.end(); i++) {
            if (i->getFirst() == key) {
                data.erase(i);
                return;
            }
        }
    }
    TData get(const TKey& key) {
        for (auto i = data.begin(); i != data.end(); i++) {
            if (i->getFirst() == key) {
                return i->getSecond();
            }
        }

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