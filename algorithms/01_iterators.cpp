/// https://hackingcpp.com/cpp/std/iterators_intro.html

// Default Iterators
// Reverse Iterators
// Iterator-Based Loops
// Example: Swap Adjacent Pairs
// Iterator Ranges
// Element Count of Iterator Range


#include <iostream>
#include <vector>
#include <algorithm> // std::min_element
#include <iterator>  // std::distance

void swap_adjacent_pairs (std::vector<int>& v);


int main(int argc, char const *argv[])
{
	std::vector<int> v {1,2,3,4,5,6,7};
	{
		auto i = std::begin(v); // i -> 1 (! C++ 11)
		auto e = std::end(v); // e -> X  (! C++ 11)
	}
	{
		auto i = rbegin(v); // i -> 7 (! C++ 11)
		auto e = rend(v); // e -> X  (! C++ 11)

		i++; // i -> 6
	}
	{
		std::vector<int> v {1,2,3};
		auto re = std::rbegin(v); // re -> 3
		auto fw = re.base(); // fw -> X (returns the corresponding normal (non-reverse) iterator)
	}
	// Iterator-Based Loops
	{
		for (auto i = begin(v); i != end(v); ++i) { std::cout << *i; } // 1234567
	}
	{
		std::vector<int> v {1, 2, 3, 4, 5, 6};
		for (auto i = rbegin(v); i != rend(v); ++i) { std::cout << *i; } // 7 6 5 4 3 2 1
	}
	// Swap Adjacent Pairs
	{
		std::vector<int> v {1,2,3,4,5,6}; // 1 2 3 4 5 6
		swap_adjacent_pairs(v); // 2 1 4 3 6 5
	}
	// Iterator Ranges
	{
		std::vector<int> v {1,2,3,4,5,6,7,8,9};
		v.erase(begin(v)+3, begin(v)+6); // 1 2 3 7 8 9
	}
	// Element Count of Iterator Range
	{
		std::vector<int> v {0,1,2,3,4,5,6,7,8};
		// size of subrange
		auto n = distance(begin(v)+2, begin(v)+7);  // int n = 5
		// size of entire container
		auto m = distance(begin(v), end(v));        // int m = 9

		std::vector<int> w {4,5,1,9,8};
		// get index of smallest element in w:
		auto argmin = std::distance(begin(w), std::min_element(begin(w),end(w)) ); // int argmin = 2
		/// !!!! Avoid using distance with iterators into non-random
		/// access containers like std::list, because the runtime
		/// will be proportional to the size of the input range!
	}

	return 0;
}

void swap_adjacent_pairs (std::vector<int>& v)
{
	if (v.size() < 2) return;
	for (auto i=begin(v), j=i+1, e=end(v); j < e; i+=2, j+=2)
	{
		std::swap(*i,*j);
	}
}