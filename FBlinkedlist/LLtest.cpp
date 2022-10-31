#include <cstdio>
#include "FileLinkedList.h"

void constructorpushandpop()
{
    std::cout << "Constructor test\n";
    FileLinkedList<char> al("al_test.bin");
    std::cout << "Clearing file\n";
    al.clear();
    std::cout << "Push test\n";
    al.push_back('A');
    al.push_back('B');
    al.push_back('C');
    al.push_back('D');
    al.push_back('E');
    al.print();
    if (al.size() != 5)
    {
        std::cout << "Size error\n";
    }
    std::cout << "Pop test (3 pops)\n";
    al.pop_back();
    al.pop_back();
    al.pop_back();
    al.print();
    if (al.size() != 2)
    {
        std::cout << "Size error\n";
    }
};
void copysegment(){
    std::cout << "Copy segment test\n";
    FileLinkedList<char> al("al_test.bin");
    std::cout << "Clearing file\n";
    al.clear();
    std::cout << "Pushing ABCDE\n";
    al.push_back('A');
    al.push_back('B');
    al.push_back('C');
    al.push_back('D');
    al.push_back('E');
    al.print();
    if (al.size() != 5)
    {
        std::cout << "Size error\n";
    }
    std::cout << "copy constructor for BCD\n";
    FileLinkedList<char> al2(++al.begin(),----al.end(),"al2_test.bin");
    al2.print();
    if (al.size() != 3)
    {
        std::cout << "Size error\n";
    }
};
void insert(){
    std::cout << "Insert test\n";
    FileLinkedList<char> al("al_test.bin");
    std::cout << "Clearing file\n";
    al.clear();
    std::cout << "Pushing ABCDE\n";
    al.push_back('A');
    al.push_back('B');
    al.push_back('C');
    al.push_back('D');
    al.push_back('E');
    al.print();
    if (al.size() != 5)
    {
        std::cout << "Size error\n";
    }
    std::cout << "Insert 'Z' Before end\n";
    al.insert(--al.end(),'Z');
    std::cout << "Insert 'X' after beginning\n";
    al.insert(++al.begin(),'X');
    al.print();
    if (al.size() != 7)
    {
        std::cout << "Size error\n";
    }
    std::cout << "Pop x 2n\n";
    al.pop_back();
    al.pop_back();
    al.print();
    if (al.size() != 5)
    {
        std::cout << "Size error\n";
    }
};
void indexandbothsets()
{
    std::cout << "Index test\n";
    FileLinkedList<char> al("al_test.bin");
    std::cout << "Clearing file\n";
    al.clear();
    std::cout << "Push ABCDE\n";
    al.push_back('A');
    al.push_back('B');
    al.push_back('C');
    al.push_back('D');
    al.push_back('E');
    al.print();
    std::cout << "al[0]: " << al[0] << std::endl;
    std::cout << "al[1]: " << al[1] << std::endl;
    std::cout << "al[2]: " << al[2] << std::endl;
    std::cout << "al[3]: " << al[3] << std::endl;
    std::cout << "al[4]: " << al[4] << std::endl;
    if (al.size() != 5)
    {
        std::cout << "Size error\n";
    }
    std::cout << "Index Set test al[3] -> Z\n";
    al.set('Z', 3);
    std::cout << "Itr Set test al.begin() -> X\n";
    al.set('X', al.begin());
    std::cout << "Itr Set test --al.end() -> X\n";
    al.set('Y', --al.end());
    al.print();
    if (al.size() != 5)
    {
        std::cout << "Size error\n";
    }
};

void erase() {
    std::cout << "Erase test\n";
    FileLinkedList<char> al("al_test.bin");
    std::cout << "Clearing file\n";
    al.clear();
    std::cout << "Pushing ABCDE\n";
    al.push_back('A');
    al.push_back('B');
    al.push_back('C');
    al.push_back('D');
    al.push_back('E');
    al.print();
    if (al.size() != 5)
    {
        std::cout << "Size error\n";
    }
    std::cout << "Erasing after begin\n";
    al.erase(++al.begin());
    al.print();
    if (al.size() != 4)
    {
        std::cout << "Size error\n";
    }
};
void runtests()
{
    std::cout << "Running tests:\n";
    // constructorpushandpop();
    //indexandbothsets();
    //insert();
    //erase();
    copysegment();
};

int main()
{
    runtests();
    return 0;
}