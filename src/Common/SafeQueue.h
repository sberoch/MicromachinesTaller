#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <string>
#include <queue>
#include <mutex>
#include <cstdint>
#include <condition_variable>

//TODO: hacerla template

template <class T>
class SafeQueue {
private:
	std::mutex mtx;
	std::condition_variable cv_empty, cv_full;
	std::queue<T> elems;
	bool blocking;

public:
	explicit SafeQueue(bool blocking = true);

	void push(const T& elem);
	void pop(T& elem);
	bool empty();
	uint32_t size();

	SafeQueue(SafeQueue&& otra) = delete;
    SafeQueue(const SafeQueue& otra) = delete;
    SafeQueue& operator=(const SafeQueue& otra) = delete;
    SafeQueue& operator=(SafeQueue&& otra) = delete;
};

template<class T>
SafeQueue<T>::SafeQueue(bool blocking): blocking(blocking) {}

template <class T>
void SafeQueue<T>::push(const T& elem) {
    {
        std::unique_lock<std::mutex> lck(mtx);
        elems.push(elem);
    }
    cv_empty.notify_one();
}

template <class T>
void SafeQueue<T>::pop(T& elem) {
    {
        std::unique_lock<std::mutex> lck(mtx);
        //Mientras este vacia y la cola sea bloqueante, espero.
        while(elems.empty() && blocking) {
            cv_empty.wait(lck);
        }
        elem = elems.front();
        elems.pop();
    }
    cv_full.notify_one();
}

template <class T>
bool SafeQueue<T>::empty() {
    std::unique_lock<std::mutex> lck(mtx);
    return elems.empty();
}

template <class T>
uint32_t SafeQueue<T>::size() {
    std::unique_lock<std::mutex> lck(mtx);
    return elems.size();
}



#endif // BLOCKING_QUEUE_H
