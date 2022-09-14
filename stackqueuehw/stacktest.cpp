#include <iostream>
#include "ArrayStack.h"

using namespace std;

int main() {
	ArrayStack<int> as1;
	for(int i = 1; i < 18; i++) {
		as1.push(i);
	}
	as1.print();
	cout << "\nDe-Q:\n";
	while(!as1.isEmpty()) {
		cout << as1.pop() << endl;
	}
}
