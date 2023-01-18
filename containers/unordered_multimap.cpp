// 0. Unordered multimap is an unordered associative container that supports equivalent keys (an unordered_multimap may contain multiple copies of each key value) and that associates values of another type with the keys.
// 1. Search, insertion, and removal have average constant-time complexity.
// 2. Internally, the elements are organised into buckets.
// 3. It uses hashing to insert elements into buckets.
// 4. This allows fast access to individual elements, since once a hash is computed,
//    it refers to the exact bucket the element is placed into.

#include <iostream>
#include <unordered_map>



int main()
{
	std::unordered_multimap <int, char> umap {{3, 'c'}, {1, '1'}, {4, 'd'}, {2, 'b'}, {4, 'd'}};

	for (auto &&e : umap)
	{
		std::cout << e.first << " - " << e.second << '\n';
	}
	///// output /////
	// 2 - b
	// 4 - d
	// 4 - d
	// 1 - 1
	// 3 - c

	auto se= umap.equal_range (4);
	while (se.first != se.second)
	{
		std::cout << "FOUND : " << se.first->first << " - " << se.first->second << '\n';
		se.first++;
	}

}
