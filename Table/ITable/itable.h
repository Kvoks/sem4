#include <iostream>
#include <list>
#include <vector>

template<class TKey, class TValue>
class TPair {
	TKey _key;
	TValue _value;
public:
	TPair() = default;
	TPair(TKey rkey, TValue rvalue): _key(rkey), _value(rvalue){}
	TValue& val(){ 
		return _value; 
	}
	TKey key(){ 
		return _key; 
	}

	bool operator==(TPair const& other) const{ 
		return _key == other._key; 
	} 

	bool operator==(TKey const& k) const{ 
		return _key == k; 
	}
	bool operator!=(TPair const& other) const {
		return _key != other._key;
	}

	bool operator!=(TKey const& k) const {
		return _key != k;
	}
};

template<class TKey, class TValue>
class ITable {
public:
	virtual TValue* found(const TKey& val) const = 0;
	virtual void insert(const TKey& key, const TValue& val) = 0;
	virtual void delet(const TKey& key) = 0;
	virtual void replase(const TKey& key, const TValue& val) = 0;
};

template<class TKey, class TValue>
class UnorderedTable: public ITable<TKey, TValue>{
	std::vector<TPair<TKey,TValue>> data;
public:
	UnorderedTable() = default;
	
	TValue* found(const TKey& key) const override {
		for (auto v : data) {
			if (v == key) {
				return &v.val();
			}
		}
		return nullptr;
	}

	void insert(const TKey& key, const TValue& val) override {
		for (auto v : data) {
			if (v == key) {
				return;
			}
		}
		data.push_back(TPair<TKey, TValue>(key, val));
	}

	void delet(const TKey& key) override {
		int i = 0;
		for (; data[i] != key; i++);
		data.erase(data.begin() + i);
	}

	void replase(const TKey& key, const TValue& val) override{
		for (auto v : data) {
			if (v == key) {
				v.val() = val;
				return;
			}
		}
	}

	size_t size() {
		return data.size();
	}
	/*TValue& operator[](size_t ind) {
		return data[ind].value;
	}

	TValue& found const(TKey& key) {
		for (int i = 0; i < data.size; i++) {
			if (data[i] == key) return data[i].value;
		}
		return NULL;
	}*/

};
/*template<typename TKey, typename TValue>
class UnorderedTableOnArray : ITable{

};

template<typename TKey, typename TValue>
void insert(TKey rkey, TValue rvalue) {
	size_t ind = found(rkey);
	if (ind == NULL) {
		ITable<TKey, TValue> tmp(rkey, rvalue);
		data[ind].append(tmp);
	}
}

template<typename TKey, typename TValue>
void remove(TKey key) {
	size_t ind = found(key);
	if (ind != NULL) {
		data[ind] = data[count];//a how
		count--;
	}
}*/

template<class TKey, class TValue>
class UnorderedTableOnList : public ITable<TKey, TValue> {
	std::list<TPair<TKey, TValue>> data;
public:
	UnorderedTableOnList() = default;

	TValue* found(const TKey& key) const override {
		for (auto& v : data) {
			if (v == key) {
				return &v.val();
			}
		}
		return nullptr;
	}

	void insert(const TKey& key, const TValue& val) override {
		for (const auto& v : data) {
			if (v == key) {
				return;
			}
		}
		data.push_back(TPair<TKey, TValue>(key, val));
	}

	void delet(const TKey& key) override {
		for (auto v = data.begin(); v != data.end(); ++v) {
			if ((*v) == key) {
				data.erase(v);
				return;
			}
		}
	}

	void replase(const TKey& key, const TValue& val) override {
		for (auto& v : data) {
			if (v == key) {
				v.val() = val;
				return;
			}
		}
	}
};