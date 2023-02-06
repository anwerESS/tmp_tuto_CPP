/// https://hackingcpp.com/cpp/std/algorithms/numeric.html

// 		iota (fill with ascending numbers) C++11
// Reductions
// 		reduce C++17
// 		transform_reduce C++17
// Legacy Operations (no parallel execution possible)
// 		accumulate (≈ reduce) C++98
// 		inner_product (≈ transform_reduce) C++98
// Scans (Prefix Sums)
// 		adjacent_difference
// 		inclusive_scan C++17
// 		exclusive_scan C++17
// 		transform_inclusive_scan C++17
// 		transform_exclusive_scan C++17
// Legacy Operations (no parallel execution possible)
// 		partial_sum (≈ inclusive_scan) C++98

#include <iostream>
#include <vector>
#include <numeric>
#include <execution>

int main(int argc, char const *argv[])
{
	// iota (fill with ascending numbers) C++11
	{
		// iota(@begin, @end, start_value)
		std::vector<int> v;
		v.resize(9,0);
		// fill subrange
		iota(begin(v)+2, begin(v)+7, 1);
		for (int x : v) { std::cout << x << ' '; }  // 0 0 1 2 3 4 5 0 0
		// fill entire vector
		iota(begin(v), end(v), 3);
		for (int x : v) { std::cout << x << ' '; }  // 3 4 5 6 7 8 9 10 11

		// iota(range, start_value) -> {@out_end, value(lst+1)}
		/*std::vector<int> v;
		v.resize(5,0);
		// NOTE: might not be available yet
		// in many standard library implementations!
		auto const result = ranges::iota(v, 3);
		std::cout << result.value;  // 8
		for (int x : v) { cout << x << ' '; }  // 3 4 5 6 7*/
	}
	//---------------------------------------------------//

	// Reductions
	{
		// reduce C++17
		{
			// reduce(@begin, @end) -> w+w1+w2..+wn
			// reduce(@begin, @end, w,) -> w+w1+w2..+wn
			// reduce(@begin, @end, w, f(O,O) -> * ) -> w+w1+w2..+wn
			// The reduction operation ⊕ must be associative and commutative, because the order in which it is applied is not guaranteed.
			std::vector<int> v {1,9,7,3,2,8};
			auto const sum = reduce(begin(v), end(v));  // 1+9+7+3+2+8 = 30
			auto const s47 = reduce(begin(v), end(v), 47);  // 47+1+9+7+3+2+8 = 77
			std::vector<double> w {2.0, 1.5, 3.0, 1.5};
			auto const product = reduce(begin(w), end(w), 1.0, std::multiplies<>{});
			// double product = 1.0 * 2.0 * 1.5 * 3.0 * 1.5 = 13.5
			// execute in parallel: #include <execution>
			auto const psum = std::reduce(std::execution::par, begin(v), end(v));

			// Make sure that the type of the initial value ω is either the same as the input elements' type or a type that can represent more values!

			// narrower initial value type might lead to loss of information:
			std::vector<double> v {1.2, 2.4};
			auto const wtf = reduce(begin(v), end(v), 1);
			std::cout << wtf;  // 4                    int ^
			auto const sum = reduce(begin(v), end(v), 1.0);
			std::cout << sum;  // 4.6               double ^^^
		}

		// transform_reduce C++17
		{
			// transform_reduce(@begin, @end, w, f(O,O) -> * , g(O) -> *) -> *
			std::vector<int> v {3,2,4};
			auto f = [](int x) { return x*x; };
			auto const rf = transform_reduce(begin(v), end(v), 1, std::plus<>{}, f);
			// rf = 1 + f(3) + f(2) + f(4) = 30

			// transform_reduce(@beg, @end, @beg2 w, f(O,O) -> * , g(O,O) -> *) -> R
			// R = w + (x1*y1)+..+ (xn*yn)
			// Both operations ⊕ and ⊗ must be associative and commutative because there is no guaranteed order in which they are applied.
			std::vector<double> x {1.0, 3.0, 5.0};
			std::vector<double> y {2.0, 4.0, 8.0};
			auto const rx1 = transform_reduce(begin(x), end(x), begin(y), 10.0);
			// rx1 = 10 + (1⋅2)+(3⋅4)+(5⋅8) = 64
			auto const rx2 = transform_reduce(
				begin(x), end(x), begin(y), 0.0,
				std::plus<>{}, std::divides<>{});
			// rx2 = 0.0 + (1/2)+(3/4)+(5/8) = 1.875
		}
	}
	//---------------------------------------------------//

	// Legacy Operations (no parallel execution possible)
	{
		// accumulate (≈ reduce) C++98
		{
			// accumulate(@begin, @end, w,) -> w+w1+w2..+wn
			// accumulate(@begin, @end, w, f(O,O) -> * ) -> w+w1+w2..+wn
			// Prefer C++17's std::reduce because it can also be executed in parallel.
			// Use accumulate only with a non-commutative or non-associative reduction operation ⊕.
			std::vector<int> v {1,9,7,3,2,8};
			auto const sum = accumulate(begin(v), end(v), 0);  // 1+9+7+3+2+8 = 30
			auto const s47 = accumulate(begin(v), end(v), 47);  // 47+1+9+7+3+2+8 = 77
			std::vector<double> w {2.0, 1.5, 3.0, 1.5};
			auto const product = accumulate(begin(w), end(w), 1.0, std::multiplies<>{});
			// double product = 1.0 * 2.0 * 1.5 * 3.0 * 1.5 = 13.5
		}

		// inner_product (≈ transform_reduce) C++98
		{
			// inner_product(@beg, @end, @beg2 w) -> R
			// inner_product(@beg, @end, @beg2 w, f(O,O) -> * , g(O,O) -> *) -> R
			// R = w + (x1*y1)+..+ (xn*yn)
			// Prefer C++17's std::transform_reduce because it can also be executed in parallel.
			std::vector<int> v {4,3,2,1};
			std::vector<int> w {10,20,30,40};
			auto const ip = inner_product(begin(v), end(v), begin(w), 50);
			// ip = 50 + (4⋅10)+(3⋅20)+(2⋅30)+(1⋅40) = 250
			std::vector<double> num {1.0, 3.0, 5.0};
			std::vector<double> den {2.0, 4.0, 8.0};
			auto const res = inner_product(
				begin(num), end(num), begin(den), 0.0,
				std::plus<>{}, std::divides<>{} );
			// res = 0.0 + (1/2)+(3/4)+(5/8) = 1.875
		}
	}
	//---------------------------------------------------//

	// Scans (Prefix Sums)
	{
		// adjacent_difference
		{
			// adjacent_difference(@beg, @end, @out) -> @out_end
			// adjacent_difference(@beg, @end, @out, f(O,O) -> *) -> @out_end
			std::vector<int> in {1,2,6,8,3,6};
			// make sure output can fit results
			std::vector<int> out;
			out.resize(in.size());
			adjacent_difference(begin(in), end(in), begin(out));
			for (int x : out) { std::cout << x << ' '; }  // 1 1 4 2 -5 3
			// C++17: can supply custom operation
			adjacent_difference(begin(in), end(in), begin(out), std::plus<>{});
			for (int x : out) { std::cout << x << ' '; }  // 1 3 8 14 11 9
			adjacent_difference(begin(in), end(in), begin(out), std::multiplies<>{});
			for (int x : out) { std::cout << x << ' '; }  // 1 2 12 48 24 18
		}

		// inclusive_scan C++17
		{
			// inclusive_scan(@beg, @end, @out) -> @out_end
			// inclusive_scan(@beg, @end, @out, f(O,O) -> *, w) -> @out_end
			std::vector<int> in {2,1,7,5,3};
			// make sure output can fit results
			std::vector<int> out;
			out.resize(in.size());
			inclusive_scan(begin(in), end(in), begin(out));
			for (int x : out) { std::cout << x << ' '; }  // 2 3 10 15 18
			inclusive_scan(begin(in), end(in), begin(out), std::minus<>{});
			for (int x : out) { std::cout << x << ' '; }  // 2 1 -6 -11 -14
			// with offset '3':
			inclusive_scan(begin(in), end(in), begin(out), std::plus<>{}, 3);
			for (int x : out) { std::cout << x << ' '; }  // 5 6 13 18 21
		}

		// exclusive_scan C++17
		{
			// inclusive_scan(@beg, @end, @out) -> @out_end
			// inclusive_scan(@beg, @end, @out, f(O,O) -> *, w) -> @out_end
			std::vector<int> in {2,1,7,5,3};
			// make sure output can fit results
			std::vector<int> out;
			out.resize(in.size());
			exclusive_scan(begin(in), end(in), begin(out), 0);
			for (int x : out) { std::cout << x << ' '; }  // 0 2 3 10 15
			// with offset '3':
			exclusive_scan(begin(in), end(in), begin(out), 3);
			for (int x : out) { std::cout << x << ' '; }  // 3 5 6 13 18
			exclusive_scan(begin(in), end(in), begin(out), 0, std::minus<>{});
			for (int x : out) { std::cout << x << ' '; }  // 0 -2 -3 -10 -15
		}
		// transform_inclusive_scan C++17
		{
			// transform_inclusive_scan(@beg, @end, @out, f(O,O) -> *, g(O,O) -> *, w) -> @out_end
			// returns value only if even and 0 if odd
			auto even_only = [](int x) { return (x & 1) ? 0 : x; };
			std::vector<int> in {2,1,6,4,3};
			// make sure output can fit results
			std::vector<int> out;
			out.resize(in.size());
			transform_inclusive_scan(
			begin(in), end(in), begin(out), std::plus<>{}, even_only);
			for (int x : out) { std::cout << x << ' '; }  // 2 2 8 12 12
			// with offset '3':
			transform_inclusive_scan(
			begin(in), end(in), begin(out), std::plus<>{}, even_only, 3);
			for (int x : out) { std::cout << x << ' '; }  // 5 5 11 15 15
			// with projection f(x) = -x2:
			transform_inclusive_scan(
			begin(in), end(in), begin(out), std::plus<>{},
			[](int x) { return -(x*x); });
			for (int x : out) { std::cout << x << ' '; }  // -4 -5 -41 -57 -66
		}

		// transform_exclusive_scan C++17
		{
			// transform_exclusive_scan(@beg, @end, @out, f(O,O) -> *, g(O,O) -> *, w) -> @out_end
			// returns value only if even and 0 if odd
			auto even_only = [](int x) { return (x & 1) ? 0 : x; };
			std::vector<int> in {2,1,6,4,3};
			// make sure output can fit results
			std::vector<int> out;
			out.resize(in.size());
			transform_exclusive_scan(
			begin(in), end(in), begin(out), 0, std::plus<>{}, even_only);
			for (int x : out) { std::cout << x << ' '; }  // 0 2 2 8 12
			// with offset '3':
			transform_exclusive_scan(
			begin(in), end(in), begin(out), 3, std::plus<>{}, even_only);
			for (int x : out) { std::cout << x << ' '; }  // 3 5 5 11 15
			// with projection f(x) = -x2:
			transform_exclusive_scan(
			begin(in), end(in), begin(out), 0, std::plus<>{}, 
			[](int x) { return -(x*x); });
			for (int x : out) { std::cout << x << ' '; }  // 0 -4 -5 -41 -57
		}
	}
	//---------------------------------------------------//

	// Legacy Operations (no parallel execution possible)
	{
		// partial_sum (≈ inclusive_scan) C++98
		{
			// partial_sum(@beg, @end, @out) -> @out_end
			// partial_sum(@beg, @end, @out, f(O,O) -> *) -> @out_end
			// Prefer C++17's std::inclusive_scan because it can also be executed in parallel.
			// Use partial_sum only, if the reduction operation ⊕ is non-associative.
			std::vector<int> in {1,1,2,2,1,1};
			// make sure output can fit results
			std::vector<int> out;
			out.resize(in.size());
			partial_sum(begin(in), end(in), begin(out));
			for (int x : out) { std::cout << x << ' '; }  // 1 2 4 6 7 8
			partial_sum(begin(in), end(in), begin(out), std::minus<>{});
			for (int x : out) { std::cout << x << ' '; }  // 1 0 -2 -4 -5 -6
		}
	}

	return 0;
}
