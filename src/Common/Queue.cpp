#include "Queue.h"
#include "ServerSnapshot.h"
#include <string>

template<class T>
void Queue<T>::put(T elem) {
	elems.push(elem);
}

template<class T>
bool Queue<T>::get(T& elem) {
	if (elems.empty()) {
		return false; 
	} else {
		elem = elems.front();
		elems.pop();
		return true;
	}
}

template class Queue<ServerSnapshot*>;
template class Queue<std::string>;
template class Queue<ServerSnapshot*>;
