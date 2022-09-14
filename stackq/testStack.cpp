#include <iostream>
#include "ArrayStack.h"

void runTests() {
	ArrayStack<int> s;
	if (!s.isEmpty()) {
		std::cout << "Not empty on creation\n";
	}
	s.push(10);
	s.print();
	if (s.isEmpty()) {
		std::cout << "Empty after push\n";
	}
	if (s.pop() != 10) {
		std::cout << "Error on pop\n";
	}
	if (!s.isEmpty()) {
		std::cout << "Not empty after pop\n";
	}
	for (int i = 0; i != 20; ++i) {
		s.push(i);
	}
	s.print();
	ArrayStack<int> s2{s};
	//ArrayStack<int> s3 = makeStack();
}

int main() {
	runTests();
}
