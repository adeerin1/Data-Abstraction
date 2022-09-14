#include "Queue.h"

template<typename T>
class ArrayQueue : public Queue<T>{
public:
~ArrayQueue() {}
void enqueue(const T &t) {};
T dequeue() {};
T peek() const {};
bool isEmpty() const {};
};
