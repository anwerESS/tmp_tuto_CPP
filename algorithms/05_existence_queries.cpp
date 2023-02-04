/// https://hackingcpp.com/cpp/std/algorithms/existence_queries.html

// any_of / all_of / none_of C++11
// count → #occurences
// count_if → #elems(f=true)


#include <iostream>
#include <algorithm>
#include <vector>



int main(int argc, char const *argv[])
{
	/// any_of / all_of / none_of
	{
		std::vector<int> v {0,2,9,1,3,8,5,2,9};
		auto const check = [](int x) { return x >= 1; };
		std::cout << all_of (begin(v)+1, begin(v)+7, check);  // true
		std::cout << any_of (begin(v)+1, begin(v)+7, check);  // true
		std::cout << none_of(begin(v)+1, begin(v)+7, check);  // false
		// in entire vector:
		std::cout << all_of (begin(v), end(v), check);  // false
		std::cout << any_of (begin(v), end(v), check);  // true
		std::cout << none_of(begin(v), end(v), check);  // false

		/// C++ 20
		/*std::cout << std::ranges::all_of (v, check);  // false
		std::cout << std::ranges::any_of (v, check);  // true
		std::cout << std::ranges::none_of(v, check);  // false*/
	}

	/// count
	{
		std::vector<int> v {5,2,9,1,3,2,5,2,2,9};
		auto n = count(begin(v)+1, begin(v)+8, 2);  // n = 3
		// count in entire vector:
		auto m = count(begin(v), end(v), 2);  // m = 4

		/// C++ 20
		/*std::vector<int> v {2,9,1,3,2,5,2};
		std::cout << std::ranges::count(v, 3);  // 1
		std::cout << std::ranges::count(v, 2);  // 3
		std::cout << std::ranges::count(v, 7);  // 0*/
	}

	/// count_if
	{
		std::vector<int> v {5,4,9,1,3,2,5,6,8,9};
		auto const is_even = [](int x) { return !(x & 1); };
		auto n = count_if (begin(v)+1, begin(v)+8, is_even);  // n = 3
		// count in entire vector:
		auto m = count_if (begin(v), end(v), is_even);  // m = 4

		/// C++ 20
		/*std::vector<int> v {4,9,1,3,2,5,6};
		auto const is_even = [](int x) { return !(x & 1); };
		auto n = std::ranges::count_if(v, is_even);  // n = 3*/
	}
	return 0;
}
