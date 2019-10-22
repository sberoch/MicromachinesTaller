//
// Created by alvaro on 30/9/19.
//

#ifndef HONEYPOT_SERVERTHREAD_H
#define HONEYPOT_SERVERTHREAD_H

#include <algorithm>
#include <thread>

class Thread {
private:
    std::thread thread;

public:
    Thread () = default;

    void start() {
        thread = std::thread(&Thread::run, this);
    }

    void join() {
        thread.join();
    }

    virtual bool isDead() = 0;
    virtual void stop() = 0;
    virtual void run() = 0;
    virtual ~Thread() = default;

    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;

    Thread(Thread&& other) noexcept {
        this->thread = std::move(other.thread);
    }

    Thread& operator=(Thread&& other) noexcept {
        this->thread = std::move(other.thread);
        return *this;
    }
};

#endif //HONEYPOT_SERVERTHREAD_H
