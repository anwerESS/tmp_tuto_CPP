/// https://hackingcpp.com/cpp/std/algorithms/removing.html

// remove / remove_if
// remove_copy / remove_copy_if
// unique / unique_copy
// erase / erase_if C++20

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>

int main(int argc, char const *argv[])
{
	// remove / remove_if
	// remove and remove_if only move the remaining elements to the front of the input range and don't resize containers or deallocate memory.
	// If you want to also modify the containing object, e.g., resize/shrink it, then
	// C++98-17 use the container's erase or resize member functions afterwards.
	// C++20 use std::erase / std::erase_if instead.
	{
		// remove(@begin, @end, value) -> @remaining_end
		std::vector<int> v {1,2,3,5,2,2,7};
		auto re = remove(begin(v), end(v), 2);
		// one could re-use the remaining space...
		fill(re, end(v), 0);
		for (int x : v) { std::cout << x << ' '; }  // 1 3 5 7 0 0 0
		// ... or shrink the vector
		v.erase(re, end(v));
		for (int x : v) { std::cout << x << ' '; }  // 1 3 5 7

		/// C++20
		// remove(range, value) -> subrange_view
		/*std::vector<int> v {1,2,3,5,2,2,7};
		auto rem = std::ranges::remove(v, 2);
		// one could re-use the remaining space...
		std::ranges::fill(rem, 0);
		for (int x : v) { std::cout << x << ' '; }  // 1 3 5 7 0 0 0
		// ... or shrink the vector
		v.erase(begin(rem), end(rem));
		for (int x : v) { std::cout << x << ' '; }  // 1 3 5 7*/

		// remove_if(@begin, @end, f(O) -> bool) -> @remaining_end
		auto const is_even = [](int x) { return !(x & 1); };
		std::vector<int> v {1,4,3,5,8,2,7};
		auto re = remove_if(begin(v), end(v), is_even);
		// one could re-use the remaining space...
		fill(re, end(v), 0);
		for (int x : v) { std::cout << x << ' '; }  // 1 3 5 7 0 0 0
		// ... or shrink the vector
		v.erase(re, end(v));
		for (int x : v) { std::cout << x << ' '; }  // 1 3 5 7

		/// C++20
		// remove(range, f(O) -> bool) -> subrange_view
		/*std::vector<int> v {1,4,3,5,8,2,7};
		auto rem = std::ranges::remove_if(v, is_even);
		// one could re-use the remaining space...
		std::ranges::fill(rem, 0);
		for (int x : v) { cout << x << ' '; }  // 1 3 5 7 0 0 0
		// ... or shrink the vector
		v.erase(begin(rem), end(rem));
		for (int x : v) { cout << x << ' '; }  // 1 3 5 7*/
	}

	// remove_copy / remove_copy_if
	{
		// remove_copy (@begin, @end, @out,  value) -> @out_end
		std::vector<int> in {1,0,1,2,3,5,2,2,7,8};
		std::vector<int> out;
		out.resize(7);
		auto re = remove_copy(begin(in)+2, begin(in)+9, begin(out), 2);
		// fit output vector
		out.erase(re, end(out));
		for (int x : out) { std::cout << x << ' '; }  // 1 3 5 7

		/// C++20
		// remove_copy (range, value) -> {@in_end, @out_end}
		/*std::vector<int> in {1,2,3,5,2,2,7};
		std::vector<int> out;
		out.resize(7);
		auto rem = std::ranges::remove_copy(in, begin(out), 2);
		// fit output vector
		out.erase(rem.out, end(out));
		for (int x : out) { cout << x << ' '; }  // 1 3 5 7*/

		// remove_copy_if(@begin, @end, @out,  f(O) -> bool) -> @out_end
		auto const is_even = [](int x) { return !(x & 1); };
		std::vector<int> in {1,0,1,4,3,5,8,2,7,8};
		std::vector<int> out;
		out.resize(7);
		auto re = remove_copy_if(begin(in)+2, begin(in)+9, begin(out), is_even);
		// fit output vector
		out.erase(re, end(out));
		for (int x : out) { std::cout << x << ' '; }  // 1 3 5 7

		/// C++20
		// remove_copy_if(range, f(O) -> bool) -> {@in_end, @out_end}
		/*std::vector<int> in {1,4,3,5,8,2,7};
		std::vector<int> out;
		out.resize(7);
		auto rem = std::ranges::remove_copy_if(in, begin(out), is_even);
		// fit output vector
		out.erase(rem.out, end(out));
		for (int x : out) { cout << x << ' '; }  // 1 3 5 7*/
	}

	// unique / unique_copy
	// unique only moves the remaining elements to the front of the input range and does not resize containers or deallocate memory. If you want to also modify the containing object, you have to do it manually afterwards.
	{
		// unique(@begin, @end) -> @remaining_end
		std::vector<int> v {4,4,1,5,3,3,3,6,3,3,1};
		auto re = unique(begin(v), end(v));
		// one could re-use the remaining space...
		fill(re, end(v), 0);
		for (int x : v) { std::cout << x << ' '; }  // 4 1 5 3 6 3 1 0 0 0 0
		// ... or shrink the vector
		v.erase(re, end(v));
		for (int x : v) { std::cout << x << ' '; }  // 4 1 5 3 6 3 1

		/// C++20
		// ranges::unique(range) ->subrange_view
		/*std::vector<int> v {4,4,1,5,3,3,3,6,3,3,1};
		auto rem = std::ranges::unique(v);
		// one could re-use the remaining space...
		std::ranges::fill(rem, 0);
		for (int x : v) { cout << x << ' '; }  // 4 1 5 3 6 3 1 0 0 0 0
		// ... or shrink the vector
		v.erase(begin(rem), end(rem));
		for (int x : v) { cout << x << ' '; }  // 4 1 5 3 6 3 1*/

		//  unique_copy(@begin, @end, @out) -> @out_end
		/*std::vector<int> in {4,4,1,5,3,3,3,6,3,3,1};
		std::vector<int> out;
		out.resize(in.size());
		auto re = unique_copy(begin(in), end(in), begin(out));
		// fit output vector
		out.erase(re, end(out));
		for (int x : out) { cout << x << ' '; }  // 4 1 5 3 6 3 1*/

		/// C++20
		// ranges::unique_copy(range) ->subrange_view
		/*std::vector<int> in {4,4,1,5,3,3,3,6,3,3,1};
		std::vector<int> out;
		out.resize(in.size());
		auto rem = std::ranges::unique_copy(in, begin(out));
		// fit output vector
		out.erase(rem.out, end(out));
		for (int x : out) { cout << x << ' '; }  // 4 1 5 3 6 3 1*/
	}

	// erase / erase_if C++20
	{
		//erase(container, value) -> erased_count
		/*std::vector<int> v {1,2,3,5,2,2,7};
		erase(v, 2);
		for (int x : v) { cout << x << ' '; }  // 1 3 5 7
		std::deque<int>  d {1,2,3,5,2,2,7};
		erase(d, 2);
		for (int x : d) { cout << x << ' '; }  // 1 3 5 7
		std::list<int>   l {1,2,3,5,2,2,7};
		erase(l, 2);
		for (int x : l) { cout << x << ' '; }  // 1 3 5 7*/

		//erase(container, f(O) -> bool) -> erased_count
		/*auto const is_even = [](int x) { return !(x & 1); };
		std::vector<int> v {1,4,3,5,8,2,7};
		erase_if (v, is_even);
		for (int x : v) { cout << x << ' '; }  // 1 3 5 7
		std::deque<int> d {1,4,3,5,8,2,7};
		erase_if (d, is_even);
		for (int x : d) { cout << x << ' '; }  // 1 3 5 7
		std::list<int> l {1,4,3,5,8,2,7};
		erase_if (l, is_even);
		for (int x : l) { cout << x << ' '; }  // 1 3 5 7*/
	}
	return 0;
}
