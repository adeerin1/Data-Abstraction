#include "Stack.h"

template<typename T>
class ArrayStack : public Stack<T> {
public:
ArrayStack() : max_sz{10},top{0},data{new T[10]} {}
ArrayStack(const ArrayStack &s) : max_sz{s.max_sz}, top{s.top}, data{new T[s.max_sz]} {
	for (int i = 0; i != max_sz; ++i) data[i] = s.data[i];
}
~ArrayStack() { delete [] data; }
void push(const T &t) {
	if (top == max_sz) {
		T* tmp = new T[max_sz*2];
		for (int i=0; i!=max_sz; ++i) tmp[i] = data[i];
		delete [] data;
		data = tmp;
		max_sz *= 2;
	}
	data[top++] = t;
};
T pop() {
	return data[--top];
};
T peek() const {};
bool isEmpty() const {
	return top == 0;	
}
void print() const {
	for (int i = 0; i != top; ++i) {
		std::cout << "i: " << i << " = " << data[i] << std::endl;
	}
}
private:
int max_sz;
int top;
T* data;
};
