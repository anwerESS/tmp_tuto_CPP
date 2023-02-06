/// https://hackingcpp.com/cpp/std/algorithms/element_modification.html

// Filling / Overwriting Ranges
// 		fill / fill_n
// 		generate / generate_n
// Changing / Replacing Values
// 		transform
// 		replace / replace_if
// 		replace_copy / replace_copy_if

#include <iostream>
#include <vector>
#include <algorithm>


int main(int argc, char const *argv[])
{
	// Filling / Overwriting Ranges
	{
		// fill / fill_n
		{
			// fill(@begin, @end, value) -> @filled_end
			std::vector<int> v {1,0,9,0,9,1,0,1};
			fill(begin(v)+2, begin(v)+7, 2);
			for (int x : v) { std::cout << x << ' '; }  // 1 0 2 2 2 2 2 1

			// fill(@begin, n, value) -> @filled_end
			std::vector<int> v {1,0,9,0,9,1,0,1};
			fill_n(begin(v)+2, 5, 2);
			for (int x : v) { std::cout << x << ' '; }  // 1 0 2 2 2 2 2 1


			/// C++20
			// fill(@begin, @end, value) -> @filled_end
			/*std::vector<int> v {9,0,9,1,0};
			std::ranges::fill(v, 2);
			for (int x : v) { cout << x << ' '; }  // 2 2 2 2 2*/
		}

		// generate / generate_n
		{
			// Example: C++14-Lambda As Generator
			{
				auto gen = [i=0]() mutable { i += 2; return i; };
				//     init-^^^    ^^^^^^^⇒ member 'i' changeable!
				std::cout << gen();  // 2
				std::cout << gen();  // 4
				std::cout << gen();  // 6
			}

			/// Example: Generator Function Class
			{
				class int_range_generator {
					int val_  = 0;
					int step_ = 1;
					public:
					int_range_generator () = default;
					explicit constexpr
					int_range_generator (int start, int step=1) noexcept:
						val_{start}, step_{step} {}
					constexpr int operator () () noexcept {
						int const old = val_;
						val_ += step_;
						return old;
					}
				};

				auto gen = int_range_generator{2,2};
				std::cout << gen();  // 2
				std::cout << gen();  // 4
				std::cout << gen();  // 6
			}

			// generate(@begin, @end, generator()-> * )
			auto gen = [i=0]() mutable { i += 2; return i; };
			std::vector<int> v;
			v.resize(7,0);
			generate(begin(v)+1, begin(v)+5, gen);
			for (int x : v) { std::cout << x << ' '; }  // 0 2 4 6 8 0 0

			// generate_n(@begin, n, generator()-> * ) -> @generator_end
			std::vector<int> v;
			v.resize(7,0);
			generate_n(begin(v)+1, 4, gen);
			for (int x : v) { std::cout << x << ' '; }  // 0 2 4 6 8 0 0

			/// C++20
			// generate_n(range, generator()-> * ) -> @end
			/*std::vector<int> v;
			v.resize(4,0);
			std::ranges::generate(v, gen);
			for (int x : v) { std::cout << x << ' '; }  // 2 4 6 8*/
		}
	}

	// Changing / Replacing Values
	{
		/// transform
		// This algorithm is also known as map in other programming languages.
		// The output target must be able to receive as many elements as there are in the input range.
		// The function (object) f must not have side effects / be stateful because the order in which it is applied to the input elements is not guaranteed.
		{
			// transform(@begin, @end, @out, f(O)-> * ) -> @out_end
			// f: 'x' → "<x>"
			auto f = [](char c) { return std::string("<") + c + ">"; };
			std::string in = "vwxyza";
			std::vector<std::string> out;
			// make sure 'out' can fit result
			out.resize(4);
			transform(begin(in)+1, begin(in)+5, begin(out), f);
			for (auto const& x : out) { std::cout << x << ' '; }  // <w> <x> <y> <z>

			// transform(@beg1, @end1, @beg2, @out, f(O,O)-> * ) -> @end
			// f: 'y',3 → "yyy"
			auto f = [](char c, int i) { return std::string(i,c); };
			std::string in1 = "wxy";
			std::vector<int> in2 = {1,2,3};
			std::vector<std::string> out;
			// make sure 'out' can fit result
			out.resize(3);
			transform(begin(in1), end(in1), begin(in2), begin(out), f);
			for (auto const& x : out) { std::cout << x << ' '; }  // w xx yyy

			/// C++20
			// transform(range, @out, f(O)-> * ) -> {@in, @out}
			/*// f: 'x' → "<x>"
			auto f = [](char c) { return std::string("<") + c + ">"; };
			std::string in = "wxyz";
			std::vector<std::string> out;
			// make sure 'out' can fit result
			out.resize(4);
			std::ranges::transform(in, begin(out), f);
			for (auto const& x : out) { cout << x << ' '; }  // <w> <x> <y> <z>*/

			/// C++20
			// transform(range1, range2, @out, f(O,O)-> * ) -> {@in1, @in2, @out}
			/*// f: 'y',3 → "yyy"
			auto f = [](char c, int i) { return std::string(i,c); };
			std::string in1 = "wxyz";
			std::vector<int> in2 = {1,2,3};
			std::vector<std::string> out;
			// make sure 'out' can fit result
			out.resize(3);
			std::ranges::transform(in1, in2, begin(out), f);
			for (auto const& x : out) { cout << x << ' '; }  // w xx yyy*/
		}

		// replace / replace_if
		{
			// replace(@begin, @end, old_val, new_val)
			std::vector<int> v {1,2,3,2,4,2,2,6};
			replace(begin(v)+2, begin(v)+7, 2, 0);
			for (int x : v) { std::cout << x << ' '; }  // 1 2 3 0 4 0 0 6

			/// C++20
			// replace(range, old_val, new_val) -> @end
			/*std::vector<int> v {3,2,4,2,2};
			std::ranges::replace(v, 2, 0);
			for (int x : v) { std::cout << x << ' '; }  // 3 0 4 0 0*/

			// replace_if(@begin, @end, f(O) -> bool, new_val)
			auto const is_even = [](int x) { return !(x & 1); };
			std::vector<int> v {1,2,3,2,5,2,2,6,7};
			replace_if (begin(v)+2, begin(v)+7, is_even, 0);
			for (int x : v) { std::cout << x << ' '; }  // 1 2 3 0 5 0 0 6 7

			/// C++20
			// replace_if(range, f(O) -> bool, new_val) -> @end
			/*auto const is_even = [](int x) { return !(x & 1); };
			std::vector<int> v {3,2,5,4,6};
			std::ranges::replace_if (v, is_even, 0);
			for (int x : v) { cout << x << ' '; }  // 3 0 5 0 0*/
		}

		// replace_copy / replace_copy_if
		{
			// replace(@begin, @end, @out, old_val, new_val) -> @out_end
			std::vector<int> in {1,2,3,2,4,2,2,6,7};
			std::vector<int> out;
			out.resize(5);
			replace_copy(begin(in)+2, begin(in)+7, begin(out), 2, 0);
			for (int x : out) { std::cout << x << ' '; }  // 3 0 4 0 0

			/// C++20
			// replace(in, @out, old_val, new_val) -> {@in_end, @out_end}
			/*std::vector<int> in {3,2,4,2,2};
			std::vector<int> out;
			out.resize(5);
			std::ranges::replace_copy(in, begin(out), 2, 0);
			for (int x : out) { cout << x << ' '; }  // 3 0 4 0 0*/

			// replace_if(@begin, @end, f(O) -> bool, new_val) -> @out_end
			auto const is_even = [](int x) { return !(x & 1); };
			std::vector<int> in {2,3,2,5,4,6,6};
			std::vector<int> out;
			out.resize(5);
			replace_copy_if (begin(in)+1, begin(in)+7, begin(out), is_even, 0);
			for (int x : out) { std::cout << x << ' '; }  // 3 0 5 0 0

			/// C++20
			// replace_if(in, f(O) -> bool, new_val) -> {@in_end, @out_end}
			/*std::vector<int> in {3,2,5,4,6};
			std::vector<int> out;
			out.resize(5);
			std::ranges::replace_copy_if (in, begin(out), is_even, 0);
			for (int x : out) { cout << x << ' '; }  // 3 0 5 0 0*/
		}
	}
	return 0;
}

