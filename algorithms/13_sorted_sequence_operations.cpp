/// https://hackingcpp.com/cpp/std/algorithms/sorted_sequence_operations.html

// Binary Searches
// 		binary_search
// 		lower_bound
// 		upper_bound
// 		equal_range
// 		includes
// Merging
// 		merge
// 		inplace_merge
// Set Operations
// 		set_union
// 		set_intersection
// 		set_difference
// 		set_symmetric_difference


#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char const *argv[])
{
	// Binary Searches
	// Searching one element in a sorted sequence of N elements can be done in O(log N) steps.
	// Finding an element in an unsorted sequence would take N steps in the worst case.
	{
		// binary_search
		{
			// binary_search(@beg, @end, val) -> bool
			// binary_search(@beg, @end, val, comp(O,O) -> bool) -> bool
			std::vector<int> v {1,2,3,4,5,6,7,8};
			// search in subrange (as in image):
			std::cout << binary_search(begin(v)+2, begin(v)+7, 4);  // true
			// search in entire vector:
			std::cout << binary_search(begin(v), end(v), 8);  // true
			std::cout << binary_search(begin(v), end(v), 9);  // false
			/// C++ 20
			// ranges::binary_search(@beg, @end, val) -> bool
			// ranges::binary_search(@beg, @end, val, comp(O,O) -> bool) -> bool
			/*std::vector<int> v {3,4,5,6,7};
			cout << std::ranges::binary_search(v, 4);  // true
			cout << std::ranges::binary_search(v, 9);  // false*/
		}

		// lower_bound
		{
			// lower_bound(@beg, @end, val) -> @1st elment found or @end
			std::vector<int> v {0,1,2,3,4,5,6,7,8};
			// find in subrange (as shown in image):
			auto i = lower_bound(begin(v)+3, begin(v)+7, 5);
			if (i != end(v)) {  // true ⇒ found
				std::cout << *i;  // 5
			}
			// find in entire vector
			auto j = lower_bound(begin(v), end(v), 2);
			if (j != end(v)) {  // true ⇒ found
				std::cout << *j;  // 2
			}

			/// C++20
			// ranges::lower_bound(range, val)  -> @1st elment found or @end
			/*std::vector<int> v {3,4,5,6,7};
			auto i = std::ranges::lower_bound(v, 5);
			if (i != end(v)) {  // true ⇒ found
			cout << *i;  // 5
			}*/

		}

		// upper_bound
		{
			// upper_bound(@beg, @end, val) -> @1st elment > value or @end
			std::vector<int> v {0,1,2,3,4,5,6,7,8};
			// find in subrange (as shown in image):
			auto i = upper_bound(begin(v)+3, begin(v)+7, 5);
			if (i != end(v)) {  // true ⇒ found
				std::cout << *i;  // 6
			}
			// find in entire vector
			auto j = upper_bound(begin(v), end(v), 2);
			if (j != end(v)) {  // true ⇒ found
				std::cout << *j;  // 3
			}

			/// C++20
			// ranges::upper_bound(range, val) -> @1st elment > value or @end
			/*std::vector<int> v {3,4,5,6,7};
			auto i = std::ranges::upper_bound(v, 5);
			if (i != end(v)) {  // true ⇒ found
			cout << *i;  // 6
			}*/
		}

		// equal_range
		{
			// equal_range(@beg, @end, val) -> {@1st elment or @end, @1st elment > value or @end}
			std::vector<int> v {1,1,2,3,4,5,5,5,6,6,7,7,8};
			// find in subrange
			auto r5 = equal_range(begin(v)+3, begin(v)+11, 5);
			// erase range of '5'
			v.erase(r5.first, r5.second);
			for (int x : v) { std::cout << x << ' '; }  // 1 1 2 3 4 6 6 7 7 8
			// find in entire vector
			auto r6 = equal_range(begin(v), end(v), 6);
			// erase range of '6'
			v.erase(r6.first, r6.second);
			for (int x : v) { std::cout << x << ' '; }  // 1 1 2 3 4 7 7 8

			/// C++20
			// ranges::equal_range(range, val) -> @1st elment or @end
			/*std::vector<int> v {3,4,5,5,5,6,6,7};
			auto [r5b,r5e] = std::ranges::equal_range(v, 5);
			// erase range
			v.erase(r5b, r5e);
			for (int x : v) { cout << x << ' '; }  // 3 4 6 6 7*/
		}

		// includes
		{
			// includes(@beg1, @end1, @beg2, @end2) -> true if range2 inside range1
			std::vector<int> r1 {0,1,2,3,4,5,6,7};
			std::vector<int> r2 {0,1,3,5,6,8,9};
			std::cout << includes(begin(r1), end(r1), begin(r2)+1, begin(r2)+5);  // true
			// entire r2 in r1?
			std::cout << includes(begin(r1), end(r1), begin(r2), end(r2));  // true

			/// C++20
			// ranges::includes(range1, range2) -> true if range2 inside range1
			/*std::vector<int> range1 {0,1,2,3,4,5,6,7};
			std::vector<int> range2 {1,3,5,6};
			cout << std::ranges::includes(range1, range2);  // true*/
		}
	}
	//----------------------------------------------------------//

	// Merging
	{
		// merge
		// Two sorted sequences can be merged into one sorted sequence in linear time.
		{
			// includes(@beg1, @end1, @beg2, @end2, @out) -> @out_end
			std::vector<int> in1 {0,2,4,6,7};
			std::vector<int> in2 {1,3,5,8};
			// make sure output can fit all elements
			std::vector<int> out;
			out.resize(in1.size() + in2.size());
			merge(begin(in1), end(in1), begin(in2), end(in2), begin(out));
			for (int x : out) { std::cout << x << ' '; }  // 0 1 2 3 4 5 6 7 8

			/// C++20
			// ranges::includes(range1, range2, @out) -> {@in1_end, @in2_end, @out_end}
			/*std::vector<int> in1 {0,2,4,6,7};
			std::vector<int> in2 {1,3,5,8};
			// make sure output can fit all elements
			std::vector<int> out;
			out.resize(in1.size() + in2.size());
			std::ranges::merge(in1, in2, begin(out));
			for (int x : out) { cout << x << ' '; }  // 0 1 2 3 4 5 6 7 8*/
		}

		// inplace_merge
		// Merges two consecutive sorted ranges: [first,middle) and [middle,last), putting the result into the combined sorted range [first,last).
		{
			// inplace_merge(@first, @second, @end)
			// inplace_merge(@first, @second, @end, compare(O,O) -> bool)
			std::vector<int> v {0,2,3,5,6,1,3,4,8};
			inplace_merge(begin(v), begin(v)+5, end(v));
			for (int x : v) { std::cout << x << ' '; }  // 0 1 2 3 3 4 5 6 8

			/// C++20
			// inplace_merge(range, @2nd, @end) -> @end
			// inplace_merge(range, @2nd, @end, cmp(O,O) -> bool) -> @end
			/*std::vector<int> v {0,2,3,5,6,1,3,4,8};
			std::ranges::inplace_merge(v, begin(v)+5);
			for (int x : v) { cout << x << ' '; }  // 0 1 2 3 3 4 5 6 8*/
		}
	}
	//----------------------------------------------------------//

	// Set Operations
	{
		// set_union
		{
			// set_union(@beg1, @end1, @beg2, @end2, @out) -> @end
			// set_union(@beg1, @end1, @beg2, @end2, @out, cmp(O,O) -> bool) -> @end
			std::vector<int> s1 {0,1,2,2,4,4,5};
			std::vector<int> s2 {1,1,3,4,5};
			// make sure output could fit all elements
			std::vector<int> out;
			out.resize(s1.size() + s2.size());
			auto e = set_union(begin(s1), end(s1), begin(s2), end(s2), begin(out));
			// shrink output to fit
			out.erase(e, end(out));
			for (int x : out) { std::cout << x << ' '; }  // 0 1 1 2 2 3 4 4 5

			/// C++20
			// set_union(range1, range2, @out) ->{@in1_end, @in2_end, @out_end}
			// set_union(range1, range2, @out, cmp(O,O) -> bool) ->{@in1_end, @in2_end, @out_end}
			/*std::vector<int> s1 {0,1,2,2,4,4,5};
			std::vector<int> s2 {1,1,3,4,5};
			// make sure output could fit all elements
			std::vector<int> out;
			out.resize(s1.size() + s2.size());
			auto res = std::ranges::set_union(s1, s2, begin(out));
			// shrink output to fit
			out.erase(res.out, end(out));
			for (int x : out) { cout << x << ' '; }  // 0 1 1 2 2 3 4 4 5*/
		}

		// set_intersection
		{
			// set_intersection(@beg1, @end1, @beg2, @end2, @out) -> @end
			// set_intersection(@beg1, @end1, @beg2, @end2, @out, cmp(O,O) -> bool) -> @end
			std::vector<int> s1 {1,2,4,6,7};
			std::vector<int> s2 {2,3,4,7};
			// make sure output could fit all elements
			std::vector<int> out;
			out.resize(std::max(s1.size(),s2.size()));
			auto e = set_intersection(begin(s1), end(s1), begin(s2), end(s2), begin(out));
			// shrink output to fit
			out.erase(e, end(out));
			for (int x : out) { std::cout << x << ' '; }  // 2 4 7

			/// C++20
			// set_intersection(range1, range2, @out) ->{@in1_end, @in2_end, @out_end}
			// set_intersection(range1, range2, @out, cmp(O,O) -> bool) ->{@in1_end, @in2_end, @out_end}
			/*std::vector<int> s1 {1,2,4,6,7};
			std::vector<int> s2 {2,3,4,7};
			// make sure output could fit all elements
			std::vector<int> out;
			out.resize(std::max(s1.size(),s2.size()));
			auto res = std::ranges::set_intersection(s1, s2, begin(out));
			// shrink output to fit
			out.erase(res.out, end(out));
			for (int x : out) { cout << x << ' '; }  // 2 4 7*/
		}

		// set_difference
		{
			// set_difference(@beg1, @end1, @beg2, @end2, @out) -> @end
			// set_difference(@beg1, @end1, @beg2, @end2, @out, cmp(O,O) -> bool) -> @end
			std::vector<int> s1 {1,2,4,6,7};
			std::vector<int> s2 {2,3,4,7};
			// make sure output could fit all elements
			std::vector<int> out;
			out.resize(std::max(s1.size(),s2.size()));
			auto e = set_difference(begin(s1), end(s1), begin(s2), end(s2), begin(out));
			// shrink output to fit
			out.erase(e, end(out));
			for (int x : out) { std::cout << x << ' '; }  // 1 6

			/// C++20
			// set_difference(range1, range2, @out) ->{@in1_end, @in2_end, @out_end}
			// set_difference(range1, range2, @out, cmp(O,O) -> bool) ->{@in1_end, @in2_end, @out_end}
			/*std::vector<int> s1 {1,2,4,6,7};
			std::vector<int> s2 {2,3,4,7};
			// make sure output could fit all elements
			std::vector<int> out;
			out.resize(std::max(s1.size(),s2.size()));
			auto res = std::ranges::set_difference(s1, s2, begin(out));
			// shrink output to fit
			out.erase(res.out, end(out));
			for (int x : out) { cout << x << ' '; }  // 1 6*/
		}

		// set_symmetric_difference
		{
			// set_symmetric_difference(@beg1, @end1, @beg2, @end2, @out) -> @end
			// set_symmetric_difference(@beg1, @end1, @beg2, @end2, @out, cmp(O,O) -> bool) -> @end
			std::vector<int> s1 {1,2,4,6,7};
			std::vector<int> s2 {2,3,4,7};
			// make sure output could fit all elements
			std::vector<int> out;
			out.resize(std::max(s1.size(),s2.size()));
			auto e = set_symmetric_difference(
			begin(s1), end(s1), begin(s2), end(s2), begin(out));
			// shrink output to fit
			out.erase(e, end(out));
			for (int x : out) { std::cout << x << ' '; }  // 1 3 6

			/// C++20
			// set_symmetric_difference(range1, range2, @out) ->{@in1_end, @in2_end, @out_end}
			// set_symmetric_difference(range1, range2, @out, cmp(O,O) -> bool) ->{@in1_end, @in2_end, @out_end}
			/*std::vector<int> s1 {1,2,4,6,7};
			std::vector<int> s2 {2,3,4,7};
			// make sure output could fit all elements
			std::vector<int> out;
			out.resize(std::max(s1.size(),s2.size()));
			auto res = std::ranges::set_symmetric_difference(s1, s2, begin(out));
			// shrink output to fit
			out.erase(res.out, end(out));
			for (int x : out) { cout << x << ' '; }  // 1 3 6*/
		}
	}

	return 0;
}
