/// https://hackingcpp.com/cpp/std/algorithms/copying.html

// copy
// copy_n (C++11)
// copy_backward
// copy_if (C++11)
// sample (C++17)
// Lambdas

#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char const *argv[])
{
	// copy
	{
		// copy(@begin, @end, @target_begin) -> @target_end
		std::vector<int> src {1,2,3,4,5,6,7,8,9,0};
		std::vector<int> tgt;
		int const n = 5;
		tgt.resize(n);
		copy(begin(src)+3, begin(src)+8, begin(tgt));
		for (int x : tgt) { std::cout << x << ' '; }  // 4 5 6 7 8

		std::vector<int> bad;
		bad.resize(2);
		copy(begin(src), end(src), begin(bad));
		//  UNDEFINED BEHAVIOR: target size is too small!

		/// C++20
		// copy(source_range, @target_begin) -> {@in, @out} ({src.end(), tgt.end()})
		/*std::vector<int> src {4,5,6,7,8};
		std::vector<int> tgt;
		tgt.resize(src.size());
		std::ranges::copy(src, begin(tgt));
		for (int x : tgt) { cout << x << ' '; }  // 4 5 6 7 8*/
	}

	// copy_n (C++11)
	{
		// copy(@begin, n, @target_begin) -> @target_end
		std::vector<int> src {1,2,3,4,5,6,7,8,9,0};
		std::vector<int> tgt;
		int const n = 5;
		tgt.resize(n);
		copy_n(begin(src)+3, n, begin(tgt));
		for (int x : tgt) { std::cout << x << ' '; }  // 4 5 6 7 8

	}

	// copy_backward
	{
		// copy(@begin, @end, @target_begin) -> @target_begin
		std::vector<int> src {1,2,3,4,5,6,7,8,9,0};
		std::vector<int> tgt;
		tgt.resize(5);
		copy_backward(begin(src)+3, begin(src)+8, end(tgt));
		for (int x : tgt) { std::cout << x << ' '; }  // 4 5 6 7 8

		/// C++20
		// copy(source_range, @target_begin) -> {@in, @out} ({src.end(), tgt.begin()})
		/*std::vector<int> src {4,5,6,7,8};
		std::vector<int> tgt;
		tgt.resize(src.size());
		std::ranges::copy_backward(src, end(tgt));
		for (int x : tgt) { cout << x << ' '; }  // 4 5 6 7 8*/
	}

	// copy_if
	{
		// copy(@begin, @end, @target, f(O)->bool) -> @target_end (C++11)
		auto const is_even = [](int x) { return !(x & 1); };
		std::vector<int> src {2,3,4,5,6,8,9,3};
		std::vector<int> tgt;
		tgt.resize(5);
		auto e = copy_if (begin(src)+2, begin(src)+7, begin(tgt), is_even);
		// how many elements copied?
		auto const copy_count = distance(begin(tgt), e);  // 3
		// resize to fit
		tgt.erase(e, end(tgt));
		for (int x : tgt) { std::cout << x << ' '; }  // 4 6 8

		/// C++20
		// copy(source, @target, f(O)->bool) -> {@in, @out} ({src.end(), lst pos copied + 1)
		auto const is_even = [](int x) { return !(x & 1); };
		std::vector<int> src {4,5,6,8,9};
		std::vector<int> tgt;
		tgt.resize(5);
		/*auto e = std::ranges::copy_if (src, begin(tgt), is_even);
		// how many elements copied?
		auto const copy_count = distance(begin(tgt), e.out);  // 3
		// resize to fit
		tgt.erase(e.out, end(tgt));
		for (int x : tgt) { cout << x << ' '; }  // 4 6 8*/
	}

	// sample (C++17)
	{
		// sample(@beg, @end, @out, n, random_generator) -> @out_end (C++17)
		// select elements with equal probability withour replacement
		#include <random>
		// 32 bit mersenne twister engine
		auto const seed = std::random_device{}();
		auto reng = std::mt19937{seed};
		int const n = 4;
		std::vector<int> samples;
		samples.resize(n);
		std::vector<int> pop {1,2,4,6,8,9};
		sample(begin(pop), end(pop), begin(samples), n, reng);
		for (int x : samples) { cout << x <<' '; }  // 1 4 6 8

		// ranges::sample(range, @out, n, random_generator) -> @end (C++20)
		/*#include <random>
		// 32 bit mersenne twister engine
		auto const seed = std::random_device{}();
		auto reng = std::mt19937{seed};
		int const n = 4;
		std::vector<int> samples;
		samples.resize(n);
		std::vector<int> pop {1,2,4,6,8,9};
		std::ranges::sample(pop, begin(samples), n, reng);
		for (int x : samples) { cout << x <<' '; }  // 1 4 6 8*/
	}

	return 0;
}
