#ifndef QUEUE_H
#define QUEUE_H

#include <queue>

template <class T>
class Queue {
private:
	std::queue<T> elems;
public:
	Queue() = default;
	void push(T elem);
	bool pop(T& elem);
};

#endif // QUEUE_H