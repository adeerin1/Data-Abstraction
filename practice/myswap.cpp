#include <iostream>
using namespace std;

template<typemane T>
void myswap(T* x, T* y) {
        T temp = *x;
        *x = *y;
       	*y = temp;
}


int main() {
	int a = 3;
	int b = 5;
	std::cout << a << " " << b << endl;
	myswap(&a, &b);
	std::cout << a << " " << b << endl;
}
