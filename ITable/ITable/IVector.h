#ifndef IVector_H
#define IVector_H

template<typename T>
class IVector {
	virtual void remove(const T& data) = 0;
	virtual void clear() = 0;
	virtual void size() = 0;
	virtual bool isEmpty() = 0;
	virtual void push_back(const T& data) = 0;
	virtual void push_front(const T& data) = 0;
};
#endif