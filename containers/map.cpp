// 1. std::map is associative container that store elements in key value combination
//    where key should be unique, otherwise it overrides the previous value.
// 2. It is implement using Self-Balance Binary Search Tree (AVL/Red Black Tree) .
// 3. It store key value pair in sorted order on the basis of key (assending/decending).
// 4. std::map is generally used in Dictionay type problems.

#include <iostream>
#include <map>
#include <string>
#include <functional>

class Person{
public:
	std::string name;
	int age;
};

int main(int argc, char const *argv[])
{
	std::map<std::string, int> Map;
	Map["AAA"] = 1;
	Map["BBB"] = 2;
	Map.insert(std::pair<std::string, int>("CCC", 3));
	Map.insert(std::make_pair("DDD", 4));
	Map["EEE"] = 5;

	for (std::map<std::string, int>::iterator it = Map.begin(); it != Map.end();++it)
	{
		std::cout << it->first << " - " << it->second << '\n';
	}

	////// output ////////
	// AAA - 1
	// BBB - 2
	// CCC - 3
	// DDD - 4
	// EEE - 5
	////////////////

	// check duplication
	std::pair<std::map<std::string, int, std::greater<std::string>>::iterator, bool> ret;
	ret = Map.insert(std::make_pair("DDD", 4));
	if(ret.second == false) // DDD existing with the value 4
		std::cout << ret.first->first << " existing with the value " << ret.first->second << '\n';

	// erase element
	std::map<std::string,int>::iterator it;
	it = Map.find("BBB");
	Map.erase(it);                   // erasing by iterator

	Map.erase("AAA");                  // erasing by key

	it= Map.find ("DDD");
	Map.erase ( it, Map.end() );    // erasing by range

	for (std::map<std::string, int>::iterator it = Map.begin(); it != Map.end();++it) // CCC - 3
	{
		std::cout << it->first << " - " << it->second << '\n';
	}

	std::map<std::string, Person, std::greater<>> Map2;
	Map2["AAA"] = {"ali", 20};
	Map2["BBB"] = {"anis", 40};
	Map2["CCC"] = {"nacer", 26};

	for (std::map<std::string, Person>::iterator it = Map2.begin(); it != Map2.end();++it) 
	{
		std::cout << it->first << " - " << it->second.name << " - "<< it->second.name << '\n';
	}

	// ////// output ////////
	// CCC - nacer - nacer
	// BBB - anis - anis
	// AAA - ali - ali
	// ////////////////
	return 0;
}
