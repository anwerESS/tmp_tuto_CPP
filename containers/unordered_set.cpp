// 0. Unordered Set is a associative container that contains set of unique objects.
// 1. Search, insertion, and removal have average constant-time complexity.
// 2. Internally, the elements are organised into buckets.
// 3. It uses hashing to insert elements into buckets.
// 4. This allows fast access to individual elements, since once a hash is computed,
//    it refers to the exact bucket the element is placed into.

// WHY UNORDERED SET?
// 0. maintain a collection of unique items with fast insertion and removal.


#include <iostream>
#include <string>
#include <unordered_set>

int main ()
{
	{
		std::unordered_set<int> myset = {7,2,2,6,3,5,1,4,2};
		auto se = myset.find(2);
		if(se != myset.end()) // FOUND : 2
			std::cout << "FOUND : " << *se << '\n';
		else
			std::cout << "NOT FOUND : " << '\n';
	}


	///////// hashing /////////
	std::unordered_set<double> myset;
	for (size_t i = 0; i < 20; i++)
	{
		myset.insert(i/1.0);
	}

	unsigned n = myset.bucket_count();

	std::cout << "myset has " << n << " buckets.\n"; // myset has 29 buckets.


	for (unsigned i=0; i<n; ++i) {
		std::cout << "bucket #" << i << " contains:";
		for (auto it = myset.begin(i); it!=myset.end(i); ++it)
			std::cout << " " << *it;
		std::cout << "\n";
	}
	/////output //////
		// bucket #0 contains: 0
		// bucket #1 contains: 16
		// bucket #2 contains: 11
		// bucket #3 contains:
		// bucket #4 contains: 6
		// bucket #5 contains: 1
		// bucket #6 contains: 4
		// bucket #7 contains:
		// bucket #8 contains:
		// bucket #9 contains:
		// bucket #10 contains: 19 13
		// bucket #11 contains:
		// bucket #12 contains:
		// bucket #13 contains:
		// bucket #14 contains: 14
		// bucket #15 contains:
		// bucket #16 contains:
		// bucket #17 contains:
		// bucket #18 contains: 3 7
		// bucket #19 contains: 2
		// bucket #20 contains:
		// bucket #21 contains: 5 12 10
		// bucket #22 contains:
		// bucket #23 contains: 9
		// bucket #24 contains: 17 8
		// bucket #25 contains:
		// bucket #26 contains: 18 15
		// bucket #27 contains:
		// bucket #28 contains:
	return 0;
}