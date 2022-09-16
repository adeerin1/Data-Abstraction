#include "ArrayList.h"
#include <iostream>

void runTests() {
	ArrayList<char> al;

	al.insert('A',0);
	al.insert('B', 0);
	al.print();
	for (auto itr = al.cbegin(); itr!= al.cend(); ++itr) {
		std::cout << *itr << std::endl;
	}
}

int main() {
	runTests();
}
