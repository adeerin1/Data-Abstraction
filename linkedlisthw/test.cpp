#include <iostream>
#include "LinkedList.h"

void runTests() {
	LinkedList<int> ll;
	ll.push_back(1);
	ll.push_back(2);
	ll.push_back(3);
	ll.push_back(4);
	if (ll.size() != 4) {
		std::cout << "Bad size after push_back\n";
	}

	for(auto itr = ll.cbegin(); itr != ll.cend(); ++itr) {
		std::cout << *itr << std::endl;
	}
	for(auto itr = ll.cbegin(); itr != ll.cend(); ) {
		std::cout << *(itr++) << std::endl;
	}
}
int main() {
	runTests();
	return 0;
}
