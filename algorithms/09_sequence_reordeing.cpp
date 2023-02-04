/// https://hackingcpp.com/cpp/std/algorithms/reordering.html

// Shift Elements
// 		reverse / reverse_copy
// 		rotate / rotate_copy
// 		shift_left C++20/23
// 		shift_right C++20/23
// 		shuffle C++11
// Sorting
// 		sort
// 		stable_sort
// 		partial_sort / partial_sort_copy
// 		nth_element
// 		is_sorted
// 		is_sorted_until
// Partitioning
// 		partition / partition_copy
// 		stable_partition
// 		is_partitioned
// 		partition_point
// 	Permutations
// 		prev_permutation / next_permutation
// 		is_permutation C++11

#include <iostream>
#include <vector>
//#include <iostream>

int main(int argc, char const *argv[])
{
	/// Shift Elements
	{
		// 	reverse / reverse_copy
		{
			// reverse(@begin, @end)
			std::vector<int> v {0,1,2,4,6,8,9,3,5};
			// reverse subrange (as shown in image):
			reverse(begin(v)+2, begin(v)+7);
			for (int x : v) { cout << x << ' '; }  // 0 1 9 8 6 4 2 3 5
			// reverse entire vector:
			reverse(begin(v), end(v));
			for (int x : v) { cout << x << ' '; }  // 5 3 2 4 6 8 9 1 0

			/// C++ 20
			// ranges::reverse(range) -> @end
			/*std::vector<int> v {2,4,6,8,9};
			std::ranges::reverse(v);
			for (int x : v) { cout << x << ' '; }  // 9 8 6 4 2*/

			// reverse_copy(@begin, @end, @copy) -> @out_end
			std::vector<int> in {0,1,2,4,6,8,9,3,5};
			std::vector<int> out;
			out.resize(5);
			reverse_copy(begin(in)+2, begin(in)+7, begin(out));
			for (int x : out) { cout << x << ' '; }  // 9 8 6 4 2

			/// C++ 20
			// ranges::reverse_copy(input, @out) -> {@in, @out}
			std::vector<int> in {2,4,6,8,9};
			std::vector<int> out;
			out.resize(in.size());
			std::ranges::reverse_copy(in, begin(out));
			for (int x : out) { cout << x <<' '; }  // 9 8 6 4 2
		}

		// 	rotate / rotate_copy
		{
			// rotate(@begin, @new_first, @end) -> @oldfirst
			std::vector<int> v {1,2,3,4,5,6,7};
			auto i = rotate(begin(v), begin(v)+2, end(v));
			for (int x : v) { cout << x <<' '; }  // 3 4 5 6 7 1 2
			// returned iterator refers to old first:
			auto const value = *i;  // 1
			auto const index = distance(begin(v), i);  // 5

			/// C++20
			// rotate(range, @new_first) -> subrange_view
			/*std::vector<int> v {1,2,3,4,5,6,7};
			auto sub = std::ranges::rotate(v, begin(v)+4);
			for (int x : v)   { cout << x <<' '; }  // 5 6 7 1 2 3 4
			for (int x : sub) { cout << x <<' '; }  // 1 2 3 4*/

			// rotate_copy(@begin, @new_first, @end, out) -> @out_end
			std::vector<int> in {1,2,3,4,5,6,7};
			std::vector<int> out;
			out.resize(in.size());
			rotate_copy(begin(in), begin(in)+2, end(in), begin(out));
			for (int x : out) { cout << x <<' '; }  // 3 4 5 6 7 1 2

			/// C++20
			// rotate_copy(input, @new_first, @out) -> {@in, @out}
			/*std::vector<int> in {1,2,3,4,5,6,7};
			std::vector<int> out;
			out.resize(in.size());
			std::ranges::rotate_copy(in, begin(in)+4, begin(out));
			for (int x : out) { cout << x <<' '; }  // 5 6 7 1 2 3 4*/
		}

		// 	shift_left C++20/23
		{
			/// C++20
			// shift_left(@begin, @end, by) -> @shifted_end
			std::vector<int> v {1,2,3,4,5,6,7,8};
			int const by = 3;
			shift_left(begin(v), end(v), by);
			for (int x : v) { cout << x <<' '; }  // 4 5 6 7 8 ? ? ? (@shifted_end -> idx[5](?))

			/// C++23
			// shift_left(range, by) -> shifted_view
			/*std::vector<int> v {1,2,3,4,5,6,7,8};
			int const by = 3;
			auto result = ranges::shift_left(v, by);
			for (int x : result) { cout << x <<' '; }  // 4 5 6 7 8*/
		}

		// 	shift_right C++20/23
		{
			/// C++20
			// shift_right(@begin, @end, by) -> @shifted_end
			std::vector<int> v {1,2,3,4,5,6,7,8};
			int const by = 3;
			shift_right(begin(v), end(v), by);
			for (int x : v) { cout << x <<' '; }  // ? ? ? 1 2 3 4 5

			/// C++23
			// shift_right(range, by) -> shifted_view
			/*std::vector<int> v {1,2,3,4,5,6,7,8};
			int const by = 3;
			auto result = ranges::shift_right(v, by);
			for (int x : result) { cout << x <<' '; }  // 1 2 3 4 5*/
		}

		// 	shuffle C++11
		{
			// shuffle(@begin, @end, random_engine)
			#include <algorithm>
			#include <random>
			// 32 bit mersenne twister engine
			auto const seed = std::random_device{}();
			auto reng = std::mt19937{seed};
			std::vector<int> v {0,1,2,3,4,5,6,7,8};
			shuffle(begin(v)+2, begin(v)+7, reng);
			for (int x : v) { cout << x <<' '; }  // 0 1 3 6 2 5 4 7 8 // ! random

			// C++20
			// shuffle(@begin, @end, random_engine) -> @end
			// 32 bit mersenne twister engine
			auto const seed = std::random_device{}();
			auto reng = std::mt19937{seed};
			std::vector<int> v {2,3,4,5,6};
			std::ranges::shuffle(v, reng);
			for (int x : v) { cout << x <<' '; } // 5 6 3 4 2 // ! random
		}
	}
	//----------------------------------------------------------//

	/// Sorting
	{
		// 	sort
		{
			// sort(@begin, @end)
			// sort(@begin, @end, compare(O,O) -> bool)
			std::vector<int> v {8,9,3,1,2,3,5,4,7,6};
			// sort subrange (as shown in image):
			sort(begin(v)+2, begin(v)+8);
			for (int x : v) { cout << x <<' '; }  // 8 9 1 2 3 3 4 5 7 6
			// sort entire vector:
			sort(begin(v), end(v));
			for (int x : v) { cout << x <<' '; }  // 1 2 3 3 4 5 6 7 8 9
			// sort vector in descending order:
			sort(begin(v), end(v), std::greater<>{});
			for (int x : v) { cout << x <<' '; }  // 9 8 7 6 5 4 3 3 2 1

			/// C++20
			// sort(range) -> @end
			// sort(range, compare(O,O) -> bool) -> @end
			std::vector<int> range {3,1,2,3,5,4};
			std::ranges::sort(range);
			for (int x : range) { cout << x <<' '; }  // 1 2 3 3 4 5
			// sort in descending order:
			std::ranges::sort(range, std::greater<>{});
			for (int x : range) { cout << x <<' '; }  // 5 4 3 3 2 1
		}

		// 	stable_sort
		{
			// stable_sort(@begin, @end)
			// stable_sort(@begin, @end, compare(O,O) -> bool)
			// stable ⇒ a stays before A (and E stays before e) even though they are equivalent with respect to case insensitive comparison
			// compares elements using operator < by default; a custom function(object) for comparing elements can be passed as 3rd argument
			#include <cctype>  // std::tolower
			auto compare_case_insensitive = [](char x, char y) {return std::tolower(x) < std::tolower(y); };
			std::string s = "gbaEAfec";
			stable_sort(begin(s)+1, begin(s)+7, compare_case_insensitive);
			cout << s;  // gaAbEefc

			/// C++20
			// stable_sort(range) -> @end
			// stable_sort(range, compare(O,O) -> bool) -> @end
			/*auto compare_case_insensitive = [](char x, char y) {
			return std::tolower(x) < std::tolower(y); };
			std::string str = "baEAfe";
			std::ranges::stable_sort(str, compare_case_insensitive);
			cout << str;  // aAbEef*/

		}

		// 	partial_sort / partial_sort_copy
		{
			// partial_sort(@begin, @nth, @end)
			// partial_sort(@begin, @nth, @end, compare(O,O) -> bool)
			// compares elements using operator < by default; a custom function(object) for comparing elements can be passed as 4th argument
			std::vector<int> v {7,4,6,2,3,5,1,9};
			// sort 4 smallest elements:
			auto const nth = begin(v) + 4;
			partial_sort(begin(v), nth, end(v));
			for (int x : v) { cout << x <<' '; }  // 1 2 3 4 7 6 5 9

			/// C++20
			// stable_sort(range, @nth) -> @end
			// stable_sort(range, @nth, compare(O,O) -> bool) -> @end
			/*std::vector<int> v {7,4,6,2,3,5,1,9};
			// sort 4 smallest elements:
			auto const nth = begin(v) + 4;
			std::ranges::partial_sort(v, nth);
			for (int x : v) { cout << x <<' '; }  // 1 2 3 4 7 6 5 9*/

			// partial_sort_copy(@iB, @iE, @oB, @oE) -> @end
			// partial_sort_copy(@iB, @iE, @oB, @oE, compare(O,O) -> bool) -> @end
			// compares elements using operator < by default; a custom function(object) for comparing elements can be passed as 5th argument
			std::vector<int> in {6,2,3,5,1};
			// get sorted copy of 3 smallest elements:
			int const n = 3;
			std::vector<int> out;
			out.resize(n);
			partial_sort_copy(begin(in), end(in), begin(out), end(out));
			for (int x : out) { cout << x <<' '; }  // 1 2 3
			// if output is larger than input:
			out.resize(100);
			auto const e = partial_sort_copy(begin(in), end(in), begin(out), end(out));
			out.erase(e, end(out));  // shrink to fit
			for (int x : out) { cout << x <<' '; }  // 1 2 3 5 6

			/// C++20
			// partial_sort_copy(input, output) -> {@in_end,@out_end}			// partial_sort_copy(input, output, compare(O,O) -> bool) -> {@in_end,@out_end}
			/*std::vector<int> in {6,2,3,5,1};
			// get sorted copy of 3 smallest elements:
			int const n = 3;
			std::vector<int> out;
			out.resize(n);
			std::ranges::partial_sort_copy(in, out);
			for (int x : out) { cout << x <<' '; }  // 1 2 3*/
		}

		// 	nth_element
		{
			// nth_element(@begin, @nth, @end)
			// compares elements using operator < by default; a custom function(object) for comparing elements can be passed as 4th argument
			std::vector<int> v {4,2,5,6,3,7,1};
			// get 5th element in sorted order
			int const n = 4;
			auto nth = begin(v) + n;
			nth_element(begin(v), nth, end(v));
			cout << *nth;  // 5

			/// C++20
			// nth_element(range, @nth) -> @end
			// compares elements using operator < by default; a custom function(object) for comparing elements can be passed as 3rd argument
			/*std::vector<int> v {4,2,5,6,3,7,1};
			// get 5th element in sorted order
			int const n = 4;
			auto nth = begin(v) + n;
			std::ranges::nth_element(v, nth);
			cout << *nth;  // 5*/

		}

		// 	is_sorted
		{
			// is_sorted(@begin, @end) -> true
			// is_sorted(@begin, @end, compare(O,O) -> bool) -> bool
			std::vector<int> v {2,3,4,5,6,1,0};
			// test subrange (as shown in image):
			cout << is_sorted(begin(v), begin(v)+5);  // true
			// test entire vector:
			cout << is_sorted(begin(v), end(v));  // false

			/// C++20
			// is_sorted(range) -> true
			// is_sorted(range, compare(O,O) -> bool) -> bool
			std::vector<int> v {2,3,4,5,6};
			cout << std::ranges::is_sorted(v);  // true
		}

		// 	is_sorted_until
		{
			// is_sorted_until(@begin, @end -> @sorted_end) // ( 1st elm not sorted)
			// is_sorted_until(@begin, @end, compare(O,O) -> bool) -> @sorted_end
			std::vector<int> v {2,3,4,5,4,2,0,7,8};
			// test from 1st to 7th (as shown in image):
			auto i = is_sorted_until(begin(v), begin(v)+7);
			// print sorted subrange
			auto const print = [](int x){ cout << x << ' '; };
			std::for_each(begin(v), i, print);  // 2 3 4 5

			/// C++20
			// is_sorted_until(range, -> @sorted_end) // ( 1st elm not sorted)
			// is_sorted_until(range, compare(O,O) -> bool) -> @sorted_end
			/*std::vector<int> v {2,3,4,5,4,2,0};
			auto const i = std::ranges::is_sorted_until(v);
			// print sorted subrange
			auto const print = [](int x){ cout << x << ' '; };
			std::for_each(begin(v), i, print);  // 2 3 4 5*/
		}
	}
	//----------------------------------------------------------//

	/// Partitioning
	{
		// 	partition / partition_copy
		{
			// partition(@begin, @end, compare(O) -> bool) -> @ftrue_end (1st el od 2nd part)
			auto const is_odd = [](int x) { return (x & 1); };
			std::vector<int> v {3,4,6,5,7,8,0};
			auto i = partition(begin(v), end(v), is_odd);
			auto const print = [](int x){ cout << x << ' '; };
			// print 1st subrange
			std::for_each(begin(v), i, print);  // 3 7 5
			// print 2nd subrange
			std::for_each(i, end(v), print);  // 6 4 8 0

			/// C++20
			// partition(range, compare(O) -> bool) -> 2nd_part_view
			auto const is_odd = [](int x) { return (x & 1); };
			std::vector<int> v {3,4,6,5,7,8,0};
			auto r2 = std::ranges::partition(v, is_odd);
			// print 2nd subrange
			for (int x : r2) { cout << x << ' '; }  // 6 4 8 0

			//  partition_copy(@beg, @end, @fTrue, @fFalse, compare(O) -> bool) -> {@fTrue_end, @fFalse_end}
			auto const is_odd = [](int x) { return (x & 1); };
			std::vector<int> in {3,4,6,5,0};
			// ensure each output could hold all elements:
			std::vector<int> out1; out1.resize(in.size());
			std::vector<int> out2; out2.resize(in.size());
			auto ends = partition_copy(begin(in), end(in), begin(out1), begin(out2), is_odd);
			// resize partitions to fit content
			out1.erase(ends.first,  end(out1));
			out2.erase(ends.second, end(out2));
			// print partitions
			for (int x : out1) { cout << x << ' '; }  // 3 5
			for (int x : out2) { cout << x << ' '; }  // 4 6 0

			/// C++20
			//  partition_copy(in @fTrue, @fFalse, compare(O) -> bool) -> {@in_end, @fTrue_end, @fFalse_end}
			/*auto const is_odd = [](int x) { return (x & 1); };
			std::vector<int> in {3,4,6,5,0};
			// ensure each output could hold all elements:
			std::vector<int> out1; out1.resize(in.size());
			std::vector<int> out2; out2.resize(in.size());
			auto ends = std::ranges::partition_copy(in, begin(out1), begin(out2), is_odd);
			// resize partitions to fit content
			out1.erase(ends.out1, end(out1));
			out2.erase(ends.out2, end(out2));
			// print partitions
			for (int x : out1) { cout << x << ' '; }  // 3 5
			for (int x : out2) { cout << x << ' '; }  // 4 6 0*/
		}

		// 	stable_partition
		{
			// stable_partition(@begin, @end, compare(O) -> bool) -> @ftrue_end (1st el od 2nd part)
			auto const is_odd = [](int x) { return (x & 1); };
			std::vector<int> v {3,4,6,5,7,8,0};
			auto i = stable_partition(begin(v), end(v), is_odd);
			auto const print = [](int x){ cout << x << ' '; };
			// print 1st subrange
			std::for_each(begin(v), i, print);  // 3 5 7
			// print 2nd subrange
			std::for_each(i, end(v), print);  // 4 6 8 0

			/// C++20
			// partition(range, compare(O) -> bool) -> 2nd_part_view
			/*auto const is_odd = [](int x) { return (x & 1); };
			std::vector<int> v {3,4,6,5,7,8,0};
			auto r2 = std::ranges::stable_partition(v, is_odd);
			// print 2nd subrange
			for (int x : r2) { cout << x << ' '; }  // 4 6 8 0*/
		}

		// 	is_partitioned
		{
			// is_partitioned(@begin, @end, compare(O) -> bool) -> bool
			auto const is_odd = [](int x) { return (x & 1); };
			std::vector<int> v {3,7,5,6,4,8,0};
			cout << is_partitioned(begin(v), end(v), is_odd);  // true

			/// C++20
			// is_partitioned(range, compare(O) -> bool) -> bool
			/*auto const is_odd = [](int x) { return (x & 1); };
			std::vector<int> v {3,7,5,6,4,8,0};
			cout << std::ranges::is_partitioned(v, is_odd);  // true*/
		}

		// 	partition_point
		{
			// partition_point(@begin, @end, compare(O) -> bool) -> fTrue_end
			auto const is_odd = [](int x) { return (x & 1); };
			std::vector<int> v {3,7,5,6,4,8,0};
			auto i = partition_point(begin(v), end(v), is_odd);
			auto const print = [](int x){ cout << x << ' '; };
			// print 1st subrange
			std::for_each(begin(v), i, print);  // 3 7 5
			// print 2nd subrange
			std::for_each(i, end(v), print);  // 6 4 8 0

			/// C++20
			// partition_point(range, compare(O) -> bool) -> fTrue_end
			/*auto const is_odd = [](int x) { return (x & 1); };
			std::vector<int> v {3,7,5,6,4,8,0};
			auto i = std::ranges::partition_point(v, is_odd);
			auto const print = [](int x){ cout << x << ' '; };
			// print 1st subrange
			std::for_each(begin(v), i, print);  // 3 7 5
			// print 2nd subrange
			std::for_each(i, end(v), print);  // 6 4 8 0*/
		}
	}
	//----------------------------------------------------------//

	/// 	Permutations
	{
		// 	prev_permutation / next_permutation
		{
			//prev_permutation (@begin, @end) -> bool
			// returns true as long as permutation is lexicographicaly smaller

			// next_permutation(@begin, @end) -> bool
			// returns true as long as permutation is lexicographicaly greater
			std::array<int,3> v {1,2,3};
			do {
				for (int x : v) { cout << x << ' '; }
				cout << '\n';
			} while( std::next_permutation(begin(v),end(v)) );
			// 1 2 3
			// 1 3 2
			// 2 1 3
			// . . .
			// 3 2 1

			/// C++ 20
			// std::ranges::prev_permutation(range) -> {@end, found}
			// found true as long as permutation is lexicographicaly smaller

			// std::ranges::next_permutation(range) -> {@end, found}
			// found true as long as permutation is lexicographicaly greater

			/*std::array<int,3> v {1,2,3};
			do {
			for (int x : v) { cout << x << ' '; } 
			cout << '\n';
			} while( std::ranges::next_permutation(v).found );*/
			// 1 2 3
			// 1 3 2
			// 2 1 3
			// . . .
			// 3 2 1
		}

		// 	is_permutation
		{
			/// C++11
			//is_permutation(@begin1, @end1, begin2) -> bool
			// returns true if range2 is a permutation of range1
			std::vector<int> v1 {1,2,3,4};
			std::vector<int> v2 {4,2,1,3};
			std::vector<int> v3 {5,0,1,2};
			cout << is_permutation(begin(v1), end(v1), begin(v2));  // true
			cout << is_permutation(begin(v1), end(v1), begin(v3));  // false

			/// C++20
			//is_permutation(range1, range2) -> bool
			// returns true if range2 is a permutation of range1
			std::vector<int> v1 {1,2,3,4};
			std::vector<int> v2 {4,2,1,3};
			std::vector<int> v3 {5,0,1,2};
			cout << std::ranges::is_permutation(v1, v2);  // true
			cout << std::ranges::is_permutation(v1, v3);  // false
		}
	}

	return 0;
}


