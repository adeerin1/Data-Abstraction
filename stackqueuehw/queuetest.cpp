#include <iostream>
#include "ArrayQueue.h"

using namespace std;

int main() {
	ArrayQueue<int> aq1;
	for(int i = 1; i < 18; i++) {
		aq1.enqueue(i);
	}
	aq1.print();
	cout << "\nDe-Q:\n";
	while(!aq1.isEmpty()) {
		cout << aq1.dequeue() << endl;	
	}

}
