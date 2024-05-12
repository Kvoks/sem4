#ifndef ITABLE_H
#define ITABLE_H

#include <iostream>

template<typename TKey, typename TData>
class ITable {
public:
	virtual void add(const TKey& key_, const TData& data_) = 0;
	virtual void remove(const TKey& key_) = 0;
	virtual TData get(const TKey& key_) = 0;
	virtual ~ITable() = default;
	virtual void clear() = 0;
	virtual size_t size() = 0;
	virtual bool isEmpty() = 0;
};
#endif