#include "Thread.h"

Thread::Thread() = default;
Thread::~Thread() = default;

Thread::Thread(Thread&& origen) {
    this->thread = std::move(origen.thread);
}
Thread& Thread::operator=(Thread&& origen) {
    this->thread = std::move(origen.thread);
    return *this;
}

void Thread::start() {
	this->thread = std::thread(&Thread::run, this);
}

void Thread::join() {
	this->thread.join();
}
