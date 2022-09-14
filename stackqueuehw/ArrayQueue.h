#include "Queue.h"

using namespace std;

template<typename T>
class ArrayQueue : public Queue<T>{
public:
ArrayQueue(): head{1}, tail{0}, max_sz{10}, data{new T[max_sz]} {}
ArrayQueue(const ArrayQueue &q) : head{q.head}, tail{q.tail}, max_sz{q.max_sz}, data{new T[q.max_sz]} {
	for(int j = head; j <= tail; j++) {
		data[j] = q.data[j];
	}
}
ArrayQueue<T> &operator=(const ArrayQueue<T> a) {
	T* s = new T[a.max_sz];
	for(int j = a.head; j <= a.tail; j++) {
		s[j] = a.data[j];
	}
	delete [] data;
	head = a.head;
	tail = a.tail;
	return *this;
}
~ArrayQueue() {delete [] data;}
void enqueue(const T &t) {
	if(tail == max_sz-1) {
		T* tempQ = new T[max_sz*2];
		for(int j = head; j <= tail; j++) {
			tempQ[j] = data[j];
		}
		delete [] data;
		data = tempQ;
		max_sz *=2;
	}
	data[++tail] = t;
};
T dequeue() {
	if(head == tail) {return data[tail--];}
	else return data[head++];
};
T peek() const {return data[head];};
bool isEmpty() const {return head > tail;};
void print() const {
	for(int j = head; j <= tail; j++) {
		cout << "j: " << data[j] <<endl;
	}
}

private:
int head, tail, max_sz;
T* data;
};

