/// https://hackingcpp.com/cpp/std/algorithms/finding.html

// Find / Locate One Element
// 		find → @value|@end
// 		find_if → @(f=true)|@end
// 		find_if_not → @(f=false)|@end C++11
// 		find_last / _if  / _if_not → view C++23
// 		find_first_of → @elem|@end
// Find Subrange in Range
// 		search → @pos|@end
// 		find_end → @pos|@end
// 		starts_with → true|false C++20
// 		ends_with → true|false C++20
// Find Run of Equal Elements
// 		adjacent_find → @pos|@end
// 		search_n → @pos|@end
// 		Query


#include <iostream>
#include <vector>
#include <algorithm>



int main(int argc, char const *argv[])
{
	///// Find / Locate One Element
	{
		/// find
		{
			// find(@begin, @end, value)
			std::vector<int> v {9,0,4,1,8,3,8,2,9};
			auto i = find(begin(v)+2, begin(v)+7, 8);
			// i != end-of-range?
			if (i != begin(v)+7) { /*true ⇒ found */}
			// find '9' in entire vector:
			auto j = find(begin(v), end(v), 9);
			if (j != end(v)) {   // true ⇒ found
				auto const value = *j;  // int value = 9
				auto const index = distance(begin(v), j);  // index = 0
			}
			auto k = find(begin(v), end(v), 7);
			if (k != end(v)) {  }    /*false ⇒ NOT found*/

			/// C++ 20
			// find(range, value)
			/*std::vector<int> v {4,1,3,8,5,8,2};
			auto i = std::ranges::find(v, 8);
			if (i != end(v)) {   // true ⇒ found
				auto const value = *i;  // int value = 8
				auto const index = distance(begin(v), i);  // index = 3
			}*/
		}

		/// find_if_not
		{
			// find_if_not(@begin, @end, f(O) -> bool)   //(O >= 2)
			std::vector<int> v {9,0,4,1,3,0,5,2,9};
			auto const f = [](int x) { return x >= 2; };
			auto i = find_if_not(begin(v)+2, begin(v)+7, f);
			// i != end-of-range?
			if (i != begin(v)+7) {  // true ⇒ found
				auto const value = *i;     // int value = 1
			}
			// find in entire vector:
			auto j = find_if_not(begin(v), end(v), f);
			if (j != end(v)) {   // true ⇒ found
				auto const value = *j;  // int value = 0
				auto const index = distance(begin(v), j);  // index = 1
			}

			/// C++ 20
			// find_if_not(range, f(O) -> bool)   //(O >= 2)
			/*std::vector<int> v {4,1,3,0};
			auto const f = [](int x) { return x >= 2; };
			auto i = std::ranges::find_if_not(v, f);
			if (i != end(v)) {   // true ⇒ found
				auto const value = *i;  // int value = 1
				auto const index = distance(begin(v), i);  // index = 1*/
		}

		/// find_last / _if  / _if_not (C++23)
		{/*
			// find_last(range, value)
			std::vector<int> v {2,1,7,1,1,5,8};
			// NOTE: might not be available yet
			// in many standard library implementations!
			auto const result = std::ranges::find_last(v, 1);
			if (not result.empty()) {   // if found
				auto const value = result.front();  // int value = 1
				auto const index = distance(begin(v),begin(result));  // index = 4
			}
			for (int x : result) { cout << x << ' '; }  // 1 5 8

			// find_last_if(range, f(O) -> bool)   //(O >= 2)
			std::vector<int> v {4,1,3,8,1};
			auto const f = [](int x) { return x >= 2; };
			// NOTE: might not be available yet
			// in many standard library implementations!
			auto const result = std::ranges::find_last_if (v, f);
			if (not result.empty()) {   // if found
				auto const value = result.front();  // int value = 8
				auto const index = distance(begin(v),begin(result));  // index = 3
			}
			for (int x : result) { cout << x << ' '; }  // 8 1

			// find_last_if_not(range, f(O) -> bool)   //(O >= 2)
			std::vector<int> v {4,0,3,1,5};
			auto const f = [](int x) { return x >= 2; };
			// NOTE: might not be available yet
			// in many standard library implementations!
			auto const result = std::ranges::find_last_if_not(v, f);
			if (not result.empty()) {   // if found
				auto const value = result.front();  // int value = 1
				auto const index = distance(begin(v),begin(result));  // index = 3
			}
			for (int x : result) { cout << x << ' '; }  // 1 5*/
		}

		/// find_first_of
		{
			// find_first_of(@Sbegin, @Send, @Sbegin, @Send)
			// returns an iterator to the 1st element in range s that compares equal to any of the elements in range w; otherwise returns @send if no such element was found
			std::vector<int> s {0,1,3,2,5,7,4,8,9,9};
			std::vector<int> w {1,4,6,5,8,7};
			auto i = find_first_of(begin(s)+1, begin(s)+9, begin(w)+1, begin(w)+4);
			// i != end-of-range?
			if (i != begin(s)+9) {  // true ⇒ found one
				auto const value = *i;     // int value = 5
				auto const index = distance(begin(s), i);  // index = 4
			}
			// find any of 'w' in all of 's':
			auto j = find_first_of(begin(s), end(s), begin(w), end(w));
			if (j != end(s)) {   // true ⇒ found one
				auto const value = *j;  // int value = 1
				auto const index = distance(begin(s), j);  // index = 1
			}

			/// C++20
			// find_first_of(@Srange, @Wrange)
			// returns an iterator to the 1st element in range s that compares equal to any of the elements in range w; otherwise returns @send if no such element was found
			/*std::vector<int> s {3,2,5,7,4,8};
			std::vector<int> w {4,6,5};
			auto i = std::ranges::find_first_of(s, w);
			if (i != end(s)) {   // true ⇒ found one
				auto const value = *i;  // int value = 5
				auto const index = distance(begin(s), i);  // index = 2
			}*/
		}
	}
	//--------------------------------------------------------//
	///// Find Subrange in Range
	{
		// search
		{
			// search(@Sbegin, @Send, @Wbein, @Wend) -> 1st occurenece of w in s
			std::vector<int> s {0,4,6,5,1,4,6,5,8,9};
			std::vector<int> w {1,4,6,5,8,9};
			// find W{4,5,6} in {4,6,5,1,4,6,5,8}
			auto i = search(begin(s)+1, begin(s)+9, begin(w)+1, begin(w)+4);
			// i != end-of-range?
			if (i != begin(s)+9) {  // true ⇒ found
				auto const value = *i;     // int value = 4
				auto const index = distance(begin(s), i);  // index = 1
			}
			// find all of 'w' in all of 's':
			auto j = search(begin(s), end(s), begin(w), end(w));
			if (j != end(s)) {   // true ⇒ found
				auto const value = *j;  // int value = 1
				auto const index = distance(begin(s), j);  // index = 4
			}


			// C++20
			// search(Srange, Wrange)
			/*std::vector<int> s {1,4,6,5,8,4,6,5};
			std::vector<int> w {4,6,5};
			auto r = std::ranges::search(s, w);
			if (not empty(r)) {
				for (int x : r) { cout << x << ' '; }  // 4 6 5
			}*/
		}

		// find_end
		{
			// find_end(@Sbegin, @Send, @Wbein, @Wend) -> last occurenece of w in s
			std::vector<int> s {0,4,6,5,1,4,6,5,8,9};
			std::vector<int> w {1,4,6,5,8,9};
			// find subrange of 'w' in subrange of 's'
			auto i = find_end(begin(s)+1, begin(s)+9, begin(w)+1, begin(w)+4);
			// i != end-of-range?
			if (i != begin(s)+9) {  // true ⇒ found
				auto const value = *i;     // int value = 4
				auto const index = distance(begin(s), i);  // index = 5
			}
			// find all of 'w' in all of 's':
			auto j = find_end(begin(s), end(s), begin(w), end(w));
			if (j != end(s)) {   // true ⇒ found
				auto const value = *j;  // int value = 1
				auto const index = distance(begin(s), j);  // index = 4
			}

			// find_end(Srange, Wrange)  -> subrange_view
			/*std::vector<int> s {1,4,6,5,8,4,6,5};
			std::vector<int> w {4,6,5};
			auto r = std::ranges::find_end(s, w);
			if (not empty(r)) {
				for (int x : r) { cout << x << ' '; }  // 4 6 5
			}*/
		}

		// starts_with C++23
		{
			// starts_with(@Sbegin, @Send, @Wbein, @Wend) -> bool(if s starts with w)
			/*std::vector<int> s {0,4,8,6,2,1,9};
			std::vector<int> w {9,4,8,6,7,3};
			// NOTE: might not be available yet
			// in many standard library implementations!
			if (std::ranges::starts_with(begin(s)+1, begin(s)+6, begin(w)+1, begin(w)+4) ) {
				cout << "yes!\n";
			}*/

			// starts_with(Srange, Wrange) -> bool(if s starts with w)
			/*std::vector<int> s {4,6,5,8,7,3};
			std::vector<int> w {4,6,5};
			// NOTE: might not be available yet
			// in many standard library implementations!
			if (std::ranges::starts_with(s, w) ) {
			cout << "yes!\n";
			}*/
		}

		// ends_with C++23
		{
			// ends_with(@Sbegin, @Send, @Wbein, @Wend) -> bool(if s ends with w)
			/*std::vector<int> s {0,4,8,6,2,1,9};
			std::vector<int> w {9,6,2,1,7,3};
			// NOTE: might not be available yet
			// in many standard library implementations!
			if (std::ranges::ends_with(begin(s)+1, begin(s)+6, begin(w)+1, begin(w)+4) ) {
				cout << "yes!\n";
			}*/

			// ends_with(Srange, Wrange) -> bool(if s ends with w)
			/*std::vector<int> s {4,6,5,8,7,3};
			std::vector<int> w {8,7,3};
			// NOTE: might not be available yet
			// in many standard library implementations!
			if (std::ranges::ends_with(s, w) ) {
				cout << "yes!\n";
			}*/
		}
	}
	//--------------------------------------------------------//

	/// Find Run of Equal Elements
	{
		// adjacent_find
		{
			// adjacent_find(@begin, @end) -> @1st occ of 2 consucetive elements (@end if no consucetive found)
			// a custom function(object) for comparing elements can be passed as 3rd argument
			std::vector<int> v {5,5,2,8,2,2,3,3,2,8};
			auto i = adjacent_find(begin(v)+1, begin(v)+8);
			// i != end-of-range?
			if (i != begin(v)+8) {  // true ⇒ found
				auto const value = *i;     // int value = 2
				auto const index = distance(begin(v), i);  // index = 4
			}
			// find in entire vector:
			auto j = adjacent_find(begin(v), end(v));
			if (j != end(v)) {   // true ⇒ found
				auto const value = *j;  // int value = 5
				auto const index = distance(begin(v), j);  // index = 0
			}

			// C++20
			// ranges::adjacent_find(range) -> @1st occ of 2 consucetive elements (@end if no consucetive found)
			// a custom function(object) for comparing elements can be passed as 2nd argument
			/*std::vector<int> v {5,2,8,2,2,3,3};
			auto i = std::ranges::adjacent_find(v);
			if (i != end(v)) {   // true ⇒ found
				auto const value = *i;  // int value = 2
				auto const index = distance(begin(v), i);  // index = 3
			}*/
		}

		// search_n
		{
			// search_n(@begin, @end, n, value) -> @1st occ of n consucetive elements (@end if no consucetive found)
			// a custom function(object) for comparing elements can be passed as 5th argument
			std::vector<int> v {0,5,2,2,8,2,2,2,9,9,9};
			const auto n = 3;
			auto i = search_n(begin(v)+1, begin(v)+9, n, 2);
			// i != end-of-range?
			if (i != begin(v)+9) {  // true ⇒ found
				auto const value = *i;     // int value = 2
				auto const index = distance(begin(v), i);  // index = 5
			}
			// find run of 3 9s in entire vector:
			auto j = search_n(begin(v), end(v), n, 9);
			if (j != end(v)) {   // true ⇒ found
				auto const value = *j;  // int value = 9
				auto const index = distance(begin(v), j);  // index = 8
			}

			// C++20
			// ranges::search_n(range, n, value) -> subrange_view
			/*std::vector<int> v {2,2,8,2,2,2,9};
			const auto n = 3;
			auto r = std::ranges::search_n(v, n, 2);
			if (not empty(r)) {   // true ⇒ found
				auto const value = r[0];  // int value = 2
				auto const index = distance(begin(v), begin(r));  // index = 3
			}*/
		}
	}
	return 0;
}
