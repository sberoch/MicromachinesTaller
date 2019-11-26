//
// Created by alvaro on 2/11/19.
//

#include "SafeCounter.h"

SafeCounter::SafeCounter(): count(0) {}

int SafeCounter::returnValueAndAddOne() {
    std::lock_guard<std::mutex> lock(this->m);
    int actualInt = count;
    this->count++;
    return actualInt;
}

SafeCounter::~SafeCounter() = default;
