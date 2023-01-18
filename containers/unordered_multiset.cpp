// 0. std::unordered_multiset is an associative container that contains set of possibly non-unique objects.
// 1. Search, insertion, and removal have average constant-time complexity.
// 2. Internally, the elements are organised into buckets.
// 3. It uses hashing to insert elements into buckets.
// 4. This allows fast access to individual elements, because after computing the hash of the value it refers to
//    the exact bucket the element is placed into.

// WHY UNORDERED_MULTISET
// 0. maintain a collection of non-uniqe items with fast insertion and removal.

#include <iostream>
#include <unordered_set>


int main()
{
	{
		std::unordered_multiset<std::string> myums = {"cow","pig","pig","chicken","pig","chicken"};

		auto myrange = myums.equal_range("pig");

		std::cout << "These pigs were found:";

		while ( myrange.first != myrange.second ) {
			std::cout << " " << *myrange.first++;
		}
		std::cout << std::endl;
	}

	{
		std::unordered_multiset <int> myset = {7,2,2,6,3,5,1,4,2};
		auto se = myset.find(2);
		if(se != myset.end()) // FOUND : 2
			std::cout << "FOUND : " << *se << '\n';
		else
			std::cout << "NOT FOUND : " << '\n';

		for (auto &&i : myset) // 4 1 5 3 6 2 2 2 7
		{
			std::cout << i << ' ';
		}
		std::cout << std::endl;
	}

	return 0;
}
