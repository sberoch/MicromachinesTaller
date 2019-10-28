#include "BlockingQueue.h"
#include <string>

BlockingQueue::BlockingQueue(const uint32_t& limit) : limit(limit) {}
  
void BlockingQueue::push(const std::string& elem) {
	{
		std::unique_lock<std::mutex> lck(mtx);
		while(elems.size() >= limit) {
		    cv_full.wait(lck);
		}
		elems.push(elem);
	}
	cv_empty.notify_one();
}

void BlockingQueue::pop(std::string& elem) {
	{
		std::unique_lock<std::mutex> lck(mtx); 
		while(elems.empty()) {
	    	cv_empty.wait(lck);
		}
		elem = elems.front();
		elems.pop();
	}
	cv_full.notify_one();
}

bool BlockingQueue::empty() {
	std::unique_lock<std::mutex> lck(mtx);
	return elems.empty();
}

uint32_t BlockingQueue::size() {
	std::unique_lock<std::mutex> lck(mtx);
	return elems.size();
}
