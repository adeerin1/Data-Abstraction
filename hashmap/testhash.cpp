#include <iostream>
#include <string>
#include <functional>
#include "HashMap.h"

using std::string;
using std::cout;
using std::endl;

int hashFunction(int i) {
	return i;
}

int runBasicTests() {
	HashMap<int,string,std::function<int(int)> > map(hashFunction);

	map[17] = "seventeen";
	cout << map[17] << endl;
	map[12] = "TWELVE";
	cout << map[12] << endl;

	if(map.erase(12) != 1) cout << "Error erasing 12!\n";
	if(map.erase(75) != 0) cout << "Error erasing 75!\n";

	if(map.find(17) == map.end()) cout << "Error finding 17\n";
	if(map.find(8) != map.end()) cout << "Error finding 8\n";

	map[5] = "five";
	map[1] = "one";
	map[-14] = "neg-fourteen";

	for(auto &v : map) {
		cout << v.first << endl;
	}

	return 0;
}

int main() {
	runBasicTests();
	return 0;
}
