#include <iostream>
#include "FileArrayList.h"

int main () {
	FileArrayList<char> al("al_test.bin");
	al.clear();
	std::cout<< "\nDefault constructor and push back test\n";
	al.push_back('A');
	al.push_back('B');
	al.push_back('C');
	al.push_back('D');
	al.push_back('E');
	al.push_back('F');
	al.print();
	if (al.size() != 6) {std::cout << "Size error\n";}
	
	std::cout<< "\nRange copy test\n";
	FileArrayList<char> al2(++++al.begin(),--al.end(),"al2.bin");
	al2.print();
	if (al2.size() != 3) {std::cout << "Size error\n";}

	std::cout<< "\nPop back test\n";
	al.pop_back();
	al.pop_back();
	al.print();
	if (al.size() != 4) {std::cout << "Size error\n";}


	std::cout<< "\nClear test\n";
	al.clear();
	al.print();
	if (al.size() != 0) {std::cout << "Size error\n";}


	std::cout<< "\nInsert Test\nInitial pushback:\n";
	al.push_back('A');
	al.push_back('C');
	al.push_back('D');
	al.push_back('E');
	al.push_back('F');
	al.push_back('G');
	al.print();
	if (al.size() != 6) {std::cout << "Size error\n";}
	auto itr = ++al.begin();
	al.insert(itr,'B');
	al.print();
	if (al.size() != 7) {std::cout << "Size error\n";}

	std::cout<< "\nIndex test\n";
	al.print();
	std::cout << "al[1]: " << al[1] << std::endl;
	std::cout << "al[2]: " << al[2] << std::endl;
	std::cout << "al[5]: " << al[5] << std::endl;
	std::cout << "al[6]: " << al[6] << std::endl;
	
	std::cout<< "\nErase test\n";
	al.print();
	std::cout << "Erase: " << *(++al.begin()) << std::endl;
	al.erase(++al.begin());
	al.print();
	if (al.size() != 6) {std::cout << "Size error\n";}

	
	std::cout<< "\nSet test\n";
	al.print();
	std::cout << "Set: " << al[4] << " to: 'Z'" << std::endl;
	al.set('Z',4);
	al.print();
	if (al.size() != 6) {std::cout << "Size error\n";}
}
