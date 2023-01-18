// 1. std::map is associative container that store elements in key value combination
//    where key should be unique, otherwise it overrides the previous value.
// 2. It is implement using Self-Balance Binary Search Tree (AVL/Red Black Tree) .
// 3. It store key value pair in sorted order on the basis of key (assending/decending).
// 4. std::map is generally used in Dictionay type problems.

#include <iostream>
#include <map>
#include <string>
#include <functional>


int main(int argc, char const *argv[])
{
	std::multimap<char, int> Multimap;
	Multimap.insert(std::make_pair('a', 1));
	Multimap.insert(std::make_pair('a', 2));
	Multimap.insert(std::make_pair('a', 3));
	Multimap.insert(std::make_pair('b', 4));
	Multimap.insert(std::make_pair('b', 5));

	// for(const auto& au : Multimap) std::cout << au.first << " - " << au.second << '\n';

	// bool isExist = Multimap.contains('a');  // std=c++20

	std::multimap<char, int>::iterator it = Multimap.find('z');
	if(it != Multimap.end()) // a - 1
		std::cout << it->first << " - " << it->second << '\n';

	std::pair<std::multimap<char, int>::iterator, std::multimap<char, int>::iterator>  range;
	range = Multimap.equal_range('a');

	std::multimap<char, int>::iterator it2;
	for (it2 = range.first; it2 != range.second; ++it2)
				std::cout << it2->first << " - " << it2->second << '\n';
	////// output ///////
	// a - 1
	// a - 2
	// a - 3
	////////////////////

	auto it3 = Multimap.lower_bound('a');
	std::cout << it3->first << " - " << it3->second << '\n'; // a - 1
	auto it4 = Multimap.upper_bound('a');
	std::cout << it4->first << " - " << it4->second << '\n'; // b - 4

	return 0;
}
