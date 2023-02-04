// 1. std multiset is an Associative Container that contains a sorted set of duplicate objects of type Key.
// 2. It is usually implemented using Red-Black Tree.
// 3. Insertion, Removal, Search have logarithmic complexity.
// 4. If we want to store user defined data type in multiset then we will have to provide
//    compare function so that multiset can store them in sorted order.
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
	std::multiset<int> multiset1{4, 1, 3, 2, 4, 5, 4}; // {1, 2, 3, 4, 4, 4, 5}
	std::cout << multiset1.count(4) << '\n'; // 3
	std::multiset<int>::iterator it = multiset1.find(2);

	if(it != multiset1.end()){
		std::cout << *it <<'\n';
		multiset1.erase(it); // set1 = {1, 3, 4, 5}
	}
	else
		std::cout <<"element not found!" <<'\n';


	///// for User defined
	std::set<Person> multiset2 {{"ali", 20}, {"anis", 40}, {"nacer", 26}}; // ali nacer anis
	//std::set<Person, std::greater<Person> > multiset2 {{"ali", 20}, {"anis", 40}, {"nacer", 26}}; // anis nacer ali
	for (const auto &au : multiset2) {std::cout << au.name << ' '; } std::cout << '\n'; //anis nacer ali

	// equal_range
	int myints[]= {77,30,16,2,30,30};
	std::multiset<int> mymultiset (myints, myints+6);  // 2 16 30 30 30 77

	typedef std::multiset<int>::iterator It;  // aliasing the iterator type used
	std::pair<It,It> ret = mymultiset.equal_range(30); //      ^        ^

	mymultiset.erase(ret.first,ret.second);

	std::cout << "mymultiset contains:";
	for (It it=mymultiset.begin(); it!=mymultiset.end(); ++it)
	std::cout << ' ' << *it;
	std::cout << '\n';
	///// output /////
	// multiset contains: 2 16 77


	return 0;
}
