/// https://hackingcpp.com/cpp/std/container_traversal.html

// Forward Traversal
// 		Range-Based Loop
// 		for_each / for_each_n
// 		Explicit Use of Iterators
// 		Index-Based Loop
// Reverse Traversal
// 		Reverse Range-Based Loop C++20
// 		Reverse for_each / for_each_n
// 		Explicit Use of Reverse Iterators
// 		Reverse Index-Based Loop
// Utilities
// 		Get Next / Previous Iterator

#include <iostream>
#include <vector>
#include <algorithm>  // std::ranges::for_each | std::for_each

// namespace ranges = std::ranges;  // alias


int main(int argc, char const *argv[])
{
	std::vector<int> v {};

	//####################{ Forward Traversal }####################//
	/// Range-Based Loop
	//  for (type variable : container)
	// +) works for all standard sequence and associative containers
	// +) container agnostic ⇒ easy to change container type
	// +) no out-of-bounds access bugs possible
	// +) no signed/unsigned index type hassle
	// +) best performance when using sequence containers due to linear access pattern (cache & prefetching friendly)
	// .) early exit possible with break;
	// -) not suited for algorithms that require random access patterns
	{
		// read-only, type cheap to copy/or copy needed:
		for (int x : v) { std::cout << x; }
		for (auto x : v) { std::cout << x; }
		// read-only, type expensive to copy:
		for (int const& x : v) { std::cout << x; }
		for (auto const& x : v) { std::cout << x; }
		// modify values:
		for (int& x : v) { std::cin >> x; }
		for (auto& x : v) { std::cin >> x; }
	}
	//--------------------------------------------------------//
	/// for_each / for_each_n
	// +) convenient if you already have a function(object) to be applied to each element
	// works for all standard sequence and associative containers
	// +) container agnostic ⇒ easy to change container type
	// +) no signed/unsigned index type hassle
	// +) self-documenting name
	// -) out-of-bounds access bugs possible with iterator ranges
	{/*
		// C++ 20
		// +) no out-of-bounds access possible
		// read-only, type cheap to copy or copy needed:
		ranges::for_each(v, [](int x){ std::cout << x; });
		ranges::for_each(v, [](auto x){ std::cout << x; });
		// read-only, type expensive to copy:
		ranges::for_each(v, [](int const& x){ std::cout << x; });
		ranges::for_each(v, [](auto const& x){ std::cout << x; });
		// modify values:
		ranges::for_each(v, [](int& x){ std::cin >> x; });
		ranges::for_each(v, [](auto& x){ std::cin >> x; });
	*/

		// +) can be used on subranges
		// -) out-of-bounds access bugs possible
		// read-only, type cheap to copy or copy needed:
		for_each(begin(v), end(v), [](int x){ std::cout << x;});
		for_each(begin(v)+2, begin(v)+5, [](auto x){ std::cout << x;});
		// read-only, type expensive to copy:
		for_each(begin(v), end(v), [](int const& x){ std::cout << x;});
		for_each(begin(v), end(v), [](auto const& x){ std::cout << x;});
		// modify values:
		for_each(begin(v), end(v), [](int& x){ std::cin >> x;});
		for_each(begin(v), end(v), [](auto& x){ std::cin >> x;});

		// +) can be used on subranges
		// -) out-of-bounds access bugs possible
		auto const n = v.size() / 2;
		// read-only, type cheap to copy or copy needed:
		for_each_n(begin(v), n, [](int x){ std::cout << x; });
		// read-only, type expensive to copy:
		for_each_n(begin(v), n, [](int const& x){ std::cout << x; });
		// modify values:
		for_each_n(begin(v), n, [](int& x){ std::cin >> x; });
	}
	//--------------------------------------------------------//
	/// Explicit Use of Iterators
	// +) container agnostic ⇒ easy to change container type
	// +) works for all standard sequence containers
	// +) no signed/unsigned index type hassle
	// +) possible to skip multiple elements
	// -)out-of-bounds access bugs possible
	// -)verbose
	{
		for (auto i = begin(v); i != end(v); ++i) { std::cout << *i; }
		for (auto i = begin(v); i != end(v); ++i) { std::cin  >> *i; }
		// read-only - using const iterators
		for (auto i = cbegin(v); i != cend(v); ++i) { std::cout << *i; }
	}
	//--------------------------------------------------------//
	/// Index-Based Loop
	// +) possible to skip multiple elements
	// -) prone to out-of-bounds access bugs
	// -) easy to write subtle bugs due to signed/unsigned index type conversions
	// -) does not work for all sequence containers ⇒ not easy to change container type
	// -) making sure that loop doesn't modify elements requires more discipline
	// -) verbose
	{
		for (std::size_t i = 0; i < v.size(); ++i) { std::cout << v[i]; }
		// explicitly read-only
		const auto& cv = v;
		for (std::size_t i = 0; i < cv.size(); ++i) { std::cout << cv[i]; }
	}

	//####################{ Reverse Traversal }####################//
	/// Reverse Range-Based Loop C++20
	// for (type variable : container | std::views::reverse)
	// +) works for all bidirectional containers
	// +) no out-of-bounds access bugs possible
	// +) no signed/unsigned index type hassle
	// .) early exit possible with break;
	{/*
		#include <ranges> //C++20
		std::vector<int> v {1, 2, 3, 4, 5, 6};
		for (int x : v | std::views::reverse) { std::cout << x << '\n'; }
		// read-only, if type cheap to copy/or copy needed
		for (auto x : v | std::views::reverse) { std::cout << x; }
		// read-only, if type expensive to copy
		for (auto const& x : v | std::views::reverse) { std::cout << x; }
		// modify values
		for (auto& x : v | std::views::reverse) { std::cin >> x; }*/
	}
	//--------------------------------------------------------//
	/// Reverse for_each / for_each_n
	// +) convenient if you already have a function(object) to be applied to each element
	// +) works for all bidirectional containers
	// +) easy to change container type
	// +) no signed/unsigned index type hassle
	// +) self-documenting name
	// -) out-of-bounds access bugs possible with iterator ranges
	{
		// C++ 20
		// +) no out-of-bounds access possible
		{/*
			#include <algorithm>  // std::ranges::for_each
			#include <ranges>     // range views
			namespace ranges = std::ranges;        // alias
			namespace views = std::ranges::views;  // alias
			// read-only, type cheap to copy or copy needed:
			ranges::for_each(views::reverse(v), [](Type x){ cout << x; });
			ranges::for_each(views::reverse(v), [](auto x){ cout << x; });
			// read-only, type expensive to copy:
			ranges::for_each(views::reverse(v), [](Type const& x){ cout << x; });
			ranges::for_each(views::reverse(v), [](auto const& x){ cout << x; });
			// modify values:
			ranges::for_each(views::reverse(v), [](Type& x){ cin >> x; });
			ranges::for_each(views::reverse(v), [](auto& x){ cin >> x; });*/
		}

		// +) can be used on subranges
		// -) out-of-bounds access bugs possible
		{
			// read-only, type cheap to copy or copy needed:
			for_each(rbegin(v), rend(v),       [](int x){ std::cout << x; });
			for_each(rbegin(v)+2, rbegin(v)+5, [](auto x){ std::cout << x; });
			// read-only, type expensive to copy:
			for_each(rbegin(v), rend(v), [](int const& x){ std::cout << x; });
			for_each(rbegin(v), rend(v), [](auto const& x){ std::cout << x; });
			// modify values:
			for_each(rbegin(v), rend(v), [](int& x){ std::cin >> x; });
			for_each(rbegin(v), rend(v), [](auto& x){ std::cin >> x; });
		}

		/// C++ 17
		// +) can be used on subranges
		// -) out-of-bounds access bugs possible
		{
			auto const n = v.size() / 2;
			// read-only, type cheap to copy or copy needed:
			for_each_n(rbegin(v), n, [](int x){ std::cout << x; });
			// read-only, type expensive to copy:
			for_each_n(rbegin(v), n, [](int const& x){ std::cout << x; });
			// modify values:
			for_each_n(rbegin(v), n, [](int& x){ std::cin >> x; });
		}
	}
	//--------------------------------------------------------//

	/// Explicit Use of Reverse Iterators
	// +) works for all bidirectional containers
	// +) no signed/unsigned index type hassle
	// +) possible to skip multiple elements
	// -) out-of-bounds access bugs possible
	// -) verbose
	{
		for (auto i = rbegin(v); i != rend(v); ++i) { std::cout << *i; }
		for (auto i = rbegin(v); i != rend(v); ++i) { std::cin  >> *i; }
		// read-only - using const iterators
		for (auto i = crbegin(v); i != crend(v); ++i) { std::cout << *i; }
	}
	//--------------------------------------------------------//

	/// Reverse Index-Based Loop
	// -) prone to out-of-bounds access bugs
	// -) easy to write subtle bugs due to unsigned size type: implicit conversions to signed int, overflow/wrap-around, …
	// -) making sure that loop doesn't modify elements requires more discipline
	// -) verbose
	{
		// std containers use unsigned size types
		// ⇒ be careful not to decrement unsigned "0"
		for (auto i = v.size(); i > 0; --i) { std::cout << v[i-1]; }
		// explicitly read-only
		const auto& cv = v;
		for (auto i = cv.size(); i > 0; --i) { std::cout << cv[i-1]; }
	}
	//--------------------------------------------------------//
	/// Utilities
	// Reverse Index-Based Loop
	// Functions std::prev and std::next provide a universal way of incrementing/decrementing iterators even if the iterator type does not support random access (e.g., it += 5).

	// However, be aware that advancing non-random access iterators (e.g., those from std::list) by N steps might be costly, i.e., involve on the order of N memory operations.
	{
		//#include <iterator>
		auto i = next(v.begin()); // 2
		auto j = next(i, 3); // 5

		std::vector<int> v2 {1,2,3,4,5,6};
		auto i = prev(v.end()); // 6
		i = prev(i); //5
		auto j = prev(i, 3); // 2

	}


	return 0;
}
