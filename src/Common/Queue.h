#ifndef QUEUE_H
#define QUEUE_H

#include <queue>

template <class T>
class Queue {
private:
	std::queue<T> elems;
public:
	Queue() = default;
	void put(T elem);
	bool get(T& elem);
};

#endif // QUEUE_H
