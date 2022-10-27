#include "ArrayList.h"
#include <iostream>

using namespace std;

void runTests() {
	//char arraylist test
	std::cout << "\nArraylist(char) tests: \n";
	ArrayList<char> al;
	al.insert('A',0);
	al.insert('B', 1);
	al.push_back('C');
	al.push_back('E');
	al[al.size()-1] = 'D';
	al.insert('F',al.size()-1);
	std::cout << "Size: " << al.size() << endl;
	al.print();

	cout << "Copy constructor: \n";
	ArrayList<char> al1(al);
	al1.print();

	cout << "Removing first: \n";
	al.remove(0);
	al.print();

	cout << "Pop back: \n";
	al.pop_back();
	al.print();

	cout << "Copy assignment \n";
	al1 = al;
	al1.print();


	//iterator tests
	std::cout << "\nIterator tests:\n";
	ArrayList<int> alint;
	for(int i = 0; i <= 100000; ++i) {
		cout << "i: " << i << " size: " << alint.size() << endl;
		alint.push_back(i);
	}
	alint.print();
	/*for (auto itr = al.cbegin(); itr!= al.cend(); itr++) {
		std::cout << *itr << std::endl;
	}
	*/
}

int main() {
	runTests();
}
