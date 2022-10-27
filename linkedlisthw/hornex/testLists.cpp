#include <iostream>
#include "LinkedList.h"

void runTests() {
	//split into seperate fns
	std::cout << "Bad size pushback test: \n";	
	LinkedList<int> ll;
	ll.push_back(5);
	ll.push_back(6);
	ll.push_back(7);
	ll.push_back(8);
	ll.push_back(9);
	ll.push_back(10);
	ll.push_back(11);
	ll.push_back(12);
	if (ll.size() != 8) {
		std::cout << "Bad size after push_back\n";
	}

	std::cout << "Iterator traversal test: \n";

	for (auto itr = ll.cbegin(); itr != ll.cend(); ++itr) {
		std::cout << *itr << std::endl;
	}
	for (auto itr = --ll.cend(); itr != --ll.cbegin(); ) {
		std::cout << *(itr--) << std::endl;
	}

	for (auto itr = --ll.cbegin(); itr != --ll.cend(); ++itr) {
		std::cout << *itr;
		std::cout << "-> prev: "<< *(--itr);
		std::cout << " next: " << *(++++itr) << std::endl;
		--itr;
	}

	std::cout << "Copy constructor test: \n";

	LinkedList<int> ll2(ll);
	ll2.push_back(13);
	ll2.pop_back();
	ll2.pop_back();
	if (ll2.size() != 7) {
		std::cout << "Bad size: after pop_back\n";
	}
	for (auto itr = ll2.cbegin(); itr != ll2.cend(); ++itr) {
		std::cout << *itr;
		std::cout << "-> prev: "<< *(--itr);
		std::cout << " next: " << *(++++itr) << std::endl;
		--itr;
	}

	std::cout << "Copy assignment test: \n";
	LinkedList<int> ll3(ll2);
	ll3 = ll;
	ll3.print();

	std::cout << "erase and clear test: \n";
	auto itr_s = ++++++ll3.begin();
	ll3.erase(itr_s);
	if (ll3.size() != 7) {
		std::cout << "Bad size after erase\n";
	}
	ll3.print();
	ll3.clear();
	ll3.print();
	if (ll3.size() != 0) {
		std::cout << "Bad size after clear\n";
	}

	std::cout << "Pushing onto cleared list: \n";
	for (int i = 1; i != 20; ++i) {
		ll3.push_back(i);
	}
	ll3.print();

	std::cout << "Weird insert test: \n";
	auto itr_r = ll.insert(++++++ll.begin(),1);
	ll.insert(itr_r,2);
	if (ll.size() != 10) {
		std::cout << "Bad size after push_back\n";
	}
	for (auto itr = ll.cbegin(); itr != ll.cend(); ++itr) {
		std::cout << *itr << std::endl;
	}

	std::cout << "Index 3: " << ll[3] << std::endl;
	ll.print();
	ll[3] = 5;
	std::cout << "Index 3 -> 5: " << ll[3] << std::endl;
	ll.print();
}

int main() {
	runTests();
	return 0;
}
