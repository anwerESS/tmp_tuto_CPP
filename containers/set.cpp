// 1. std::set is an Associative Container that contains a sorted set of unique objects of type Key.
// 2. It is usually implemented using Red-Black Tree.
// 3. Insertion, Removal, Search have logarithmic complexity.
// 4. If we want to store user defined data type in set then we will have to provide
//    compare function so that set can store them in sorted order.
// 5. We can pass the order of sorting while constructing set object.


#include <iostream>
#include <set>
#include <string>
#include <functional>

class Person{
public:
	std::string name;
	int age;

	bool operator < (const Person &other) const {return age < other.age;}
	bool operator > (const Person &other) const {return age > other.age;}
};

int main(int argc, char const *argv[])
{
	std::set<int> set1{4, 1, 3, 2, 4, 5, 4}; // {1, 2, 3, 4, 5}
	std::cout << set1.count(4) << '\n'; // 1
	std::set<int>::iterator it = set1.find(2);
	if(it != set1.end()){
		std::cout << *it <<'\n';
		set1.erase(it); // set1 = {1, 3, 4, 5}
	}
	else
		std::cout <<"element not found!" <<'\n';


	///// for classes
	// std::set<Person> set2 {{"ali", 20}, {"anis", 40}, {"nacer", 26}};
	std::set<Person, std::greater<Person> > set2 {{"ali", 20}, {"anis", 40}, {"nacer", 26}};
	for (const auto &au : set2) {std::cout << au.name << ' '; } std::cout << '\n'; //anis nacer ali

	return 0;
}
