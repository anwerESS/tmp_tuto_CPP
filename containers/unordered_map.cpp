// 0. std::unordered_map is an associative container that contains key-value pairs with unique keys.
// 1. Search, insertion, and removal have average constant-time complexity.
// 2. Internally, the elements are organised into buckets.
// 3. It uses hashing to insert elements into buckets.
// 4. This allows fast access to individual elements, because after computing the hash of the value it refers to
//    the exact bucket the element is placed into.

// WHY UNORDERED_MAP
// 0. maintain a collection of uniqe {key:value} pairs with fast insertion and removal.


#include <iostream>
#include <unordered_map>



int main()
{
	std::unordered_map <int, char> umap {{3, 'c'}, {1, '1'}, {4, 'd'}, {2, 'b'}, {4, 'd'}};

	for (auto &&e : umap)
	{
		std::cout << e.first << " - " << e.second << '\n';
	}
	///// output /////
	// 2 - b
	// 4 - d
	// 1 - 1
	// 3 - c

	auto se= umap.find (4);
	if(se != umap.end()) // FOUND : 4 - d
		std::cout << "FOUND : " << se->first << " - " << se->second << '\n';
	else
		std::cout << "NOT FOUND : " << '\n';

	return 0;
}
