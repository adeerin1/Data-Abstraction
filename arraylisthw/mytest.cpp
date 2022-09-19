#include "ArrayList.h"
#include <iostream>

void runTests() {
	ArrayList<char> al;

	al.insert('A',0);
	al.insert('B', 0);
	al[1] = 'C';
	char c = al[1];
	std:: cout << c << std::endl;
	al.print();
	for (auto itr = al.cbegin(); itr!= al.cend(); ++itr) {
		std::cout << *itr << std::endl;
	}
}

int main() {
	runTests();
}
