#include "Queue.h"
#include "Event/SnapshotEvent.h"
#include "Event/LobbySnapshot.h"
#include <string>

template<class T>
void Queue<T>::push(T elem) {
	elems.push(elem);
}

template<class T>
bool Queue<T>::pop(T& elem) {
	if (elems.empty()) {
		return false; 
	} else {
		elem = elems.front();
		elems.pop();
		return true;
	}
}

template class Queue<SnapshotEvent*>;
template class Queue<LobbySnapshot*>;
template class Queue<std::string>;