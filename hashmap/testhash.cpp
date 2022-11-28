#include <iostream>
#include <string>
#include <functional>
#include "HashMap.h"

using std::cout;
using std::endl;
using std::string;

int hashFunction(int i)
{
	return i;
}

void mapTest()
{
	cout << "\nMap test:\nMapping 17, 12\n";
	HashMap<int, string, std::function<int(int)>> map(hashFunction);

	map[17] = "seventeen";
	map[12] = "TWELVE";
	map.print();
}

void eraseTest()
{
	cout << "\nErase test:\nMapping 17, 12, 5, 8\n";
	HashMap<int, string, std::function<int(int)>> map(hashFunction);

	map[17] = "seventeen";
	map[12] = "TWELVE";
	map[5] = "five";
	map[8] = "Eight";

	cout << "Erasing 12 and 75 with key values:\n";
	if (map.erase(12) != 1)
		cout << "Error erasing 12!\n";
	if (map.erase(75) != 0)
		cout << "Error erasing 75!\n";
	if (map.size() != 3)
		cout << "Size error\n";
	cout << "Hashmap:\n";
	map.print();

	cout << "Erasing begin iterator:\n";
	auto rover = ++(map.begin());
	auto begin = map.cbegin();
	cout << "begin: " << (*begin).first << ", " << (*begin).second << endl;
	cout << "++begin: " << (*rover).first << ", " << (*rover).second << endl;
	auto result = map.erase(begin);
	if (result != rover)
		cout << "Error erasing begin()!\n";
	if (map.size() != 2)
		cout << "Size error\n";
	cout << "Hashmap after erase: \n";
	map.print();
}

void findTest()
{
	cout << "\nFind test:\nMapping 17,12\n";
	HashMap<int, string, std::function<int(int)>> map(hashFunction);

	map[17] = "seventeen";
	map[12] = "TWELVE";
	cout << "Hashmap:\n";
	map.print();
	cout << "Finding 17 and 8 with key value:\n";
	if (map.find(17) == map.end())
		cout << "Error finding 17\n";
	if (map.find(8) != map.end())
		cout << "Error finding 8\n";
}

void printTest()
{
	cout << "Print test:\nMapping 17, 12, 5, 1, -14\n";
	HashMap<int, string, std::function<int(int)>> map(hashFunction);

	map[17] = "seventeen";
	map[12] = "TWELVE";
	map[5] = "five";
	map[1] = "one";
	map[-14] = "neg-fourteen";
	map.print();
}

void countTest()
{
	cout << "\nCount test:\nMapping 17, 12, 9, -14\n";
	HashMap<int, string, std::function<int(int)>> map(hashFunction);

	map[17] = "seventeen";
	map[12] = "TWELVE";
	map[9] = "nine";
	map[-14] = "neg-fourteen";
	map.print();
	cout << "Count(17): " << map.count(17) << endl;
	cout << "Count(15): " << map.count(15) << endl;
	cout << "Count(12): " << map.count(12) << endl;
	cout << "Count(9): " << map.count(9) << endl;
	cout << "Count(-14): " << map.count(-14) << endl;
}

void sizeTest()
{
	cout << "Size test:\nMapping 17, 12, 9, -14\n";
	HashMap<int, string, std::function<int(int)>> map(hashFunction);

	if (map.empty() == true)
		cout << "Map is empty\n";
	else
		cout << "Map is not empty\n";
	cout << "Map size: " << map.size() << endl;
	map[17] = "seventeen";
	map[12] = "TWELVE";
	map[9] = "nine";
	map[-14] = "neg-fourteen";
	map.print();
	if (map.empty() == true)
		cout << "Map is empty\n";
	else
		cout << "Map is not empty\n";
	cout << "Map size: " << map.size() << endl;
	cout << "Clear test:\n";
	map.clear();
	map.print();
	if (map.empty() == true)
		cout << "Map is empty\n";
	else
		cout << "Map is not empty\n";
	cout << "Map size: " << map.size() << endl;
}

void hashEqualTest()
{
	cout << "Hash Equal test:\nmap1: 17, 12, -14, 9\n";
	HashMap<int, string, std::function<int(int)>> map1(hashFunction);
	map1[17] = "seventeen";
	map1[12] = "TWELVE";
	map1[-14] = "neg-fourteen";
	map1[9] = "nine";

	map1.print();
	if (map1.empty() == true)
		cout << "Map1 is empty\n";
	else
		cout << "Map1 is not empty\n";
	cout << "Map1 size: " << map1.size() << endl;

	cout << "map2: 12, 17, 9, -14\n";
	HashMap<int, string, std::function<int(int)>> map2(hashFunction);
	map2[12] = "TWELVE";
	map2[17] = "seventeen";
	map2[9] = "nine";
	map2[-14] = "neg-fourteen";
	map2.print();
	if (map2.empty() == true)
		cout << "Map2 is empty\n";
	else
		cout << "Map2 is not empty\n";
	cout << "Map2 size: " << map2.size() << endl;

	cout << "Same data, different order\n";
	if (map1 == map2)
		cout << "\nmap1 and map2 are equal\n";
	else
		cout << "map1 and map2 are not equal\n";

	cout << "map3: 12, 17, 10, -14\n";
	HashMap<int, string, std::function<int(int)>> map3(hashFunction);
	map3[12] = "TWELVE";
	map3[17] = "seventeen";
	map3[10] = "ten";
	map3[-14] = "neg-fourteen";
	map3.print();
	if (map3.empty() == true)
		cout << "Map3 is empty\n";
	else
		cout << "Map3 is not empty\n";
	cout << "Map3 size: " << map3.size() << endl;

	cout << "Different keys\n";
	if (map1 == map3)
		cout << "\nmap1 and map3 are equal\n";
	else
		cout << "map1 and map3 are not equal\n";

	cout << "map4: 12, 17, 9, -14\n";
	HashMap<int, string, std::function<int(int)>> map4(hashFunction);
	map4[12] = "TWELVE";
	map4[17] = "seventeen";
	map4[10] = "NINE";
	map4[-14] = "neg-fourteen";
	map4.print();
	if (map4.empty() == true)
		cout << "Map4 is empty\n";
	else
		cout << "Map4 is not empty\n";
	cout << "Map4 size: " << map4.size() << endl;

	cout << "Different values for key 9, testing !=\n";
	if (map1 != map4)
		cout << "\nmap1 and map4 are not equal\n";
	else
		cout << "map1 and map4 are equal\n";
}

void insertTest()
{
	cout << "Insert test:\nMapping 17, 12, 9, -14\n";
	HashMap<int, string, std::function<int(int)>> map(hashFunction);

	map[17] = "seventeen";
	map[12] = "TWELVE";
	map[9] = "nine";
	map[-14] = "neg-fourteen";
	map.print();
	if (map.empty() == true)
		cout << "Map is empty\n";
	else
		cout << "Map is not empty\n";
	cout << "Map size: " << map.size() << endl;
	cout << "Inserting [10,ten], [9,NINE]\n";
	std::pair<int, string> pair(10, "ten");
	map.insert(pair);
	pair.first = 9;
	pair.second = "NINE";
	map.insert(pair);
	map.print();
	if (map.empty() == true)
		cout << "Map is empty\n";
	else
		cout << "Map is not empty\n";
	cout << "Map size: " << map.size() << endl;

	cout << "\nInsert range test:\nMapping to map2: 1, 2, 3, 4, -14\n";
	HashMap<int, string, std::function<int(int)>> map2(hashFunction);

	map2[1] = "one";
	map2[2] = "two";
	map2[3] = "three";
	map2[4] = "four";
	map2[-14] = "neg-FOURTEEN";
	map2.print();
	if (map2.empty() == true)
		cout << "Map2 is empty\n";
	else
		cout << "Map2 is not empty\n";
	cout << "Map2 size: " << map2.size() << endl;

	cout << "Inserting map2 into map\n";
	map.insert(map2.begin(), map2.end());
	map.print();
	if (map.empty() == true)
		cout << "Map is empty\n";
	else
		cout << "Map is not empty\n";
	cout << "Map size: " << map.size() << endl;
}
void runBasicTests()
{
	// mapTest();
	eraseTest();
	// findTest();
	// printTest();
	// countTest();
	// sizeTest();
	// hashEqualTest();
	insertTest();
}

int main()
{
	runBasicTests();
	return 0;
}
