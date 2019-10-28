#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <string>
#include <queue>
#include <mutex>
#include <cstdint>
#include <condition_variable>

//TODO: hacerla template

class BlockingQueue {
private:
	uint32_t limit;
	std::mutex mtx;
	std::condition_variable cv_empty, cv_full;
	std::queue<std::string> elems;
public:
	explicit BlockingQueue(const uint32_t& limit);

	void push(const std::string& elem);
	void pop(std::string& elem);
	bool empty();
	uint32_t size();

	BlockingQueue(BlockingQueue&& otra) = delete;
    BlockingQueue(const BlockingQueue& otra) = delete;
    BlockingQueue& operator=(const BlockingQueue& otra) = delete;
    BlockingQueue& operator=(BlockingQueue&& otra) = delete;
};

#endif // BLOCKING_QUEUE_H
