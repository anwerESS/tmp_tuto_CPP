/// https://hackingcpp.com/cpp/std/algorithms/min_max.html
#include <iostream>
#include <algorithm>
#include <vector>

// min
// max
// minmax C++11
// clamp C++17
// min_element → @position
// max_element → @position
// minmax_element → {@min,@max} C++11

int main(int argc, char const *argv[])
{
	/// min
	{
		// min(a, b) → a if (a < b) is true, b otherwise
		// min(a, b, cmp(o,o)→bool) → a if cmp(a,b) is true, b otherwise
		int const a = 2, b = 9;
		int x = std::min(a,b);  // int x = 2

		struct P { int q; char c;};
		P pmin = std::min(P{1,'y'}, P{2,'x'}, [](P p1, P p2){ return p1.q < p2.q; });  // P pmin {1,'y'};

		/// C++ 11
		// min({v1,v2,v3,…}) → smallest_value C++11
		// min({v1,v2,v3,…}, cmp(o,o)→bool) → smallest_value
		// All elements in the input list { … } must have the same type!
		int x = std::min({3,4,b,3,a,8});  // int x = 2

		/// C++ 20
		// ranges::min(range) → smallest_value
		// ranges::min(range, cmp(o,o)→bool) → smallest_value

		/*std::vector<int> v {7,9,3,5,3,1,4,8};
		auto x = std::ranges::min(v);  // int x = 1
		struct P { int q; char c; };
		std::vector<P> const w {P{3,'a'},P{1,'c'},P{2,'b'}};
		auto pmin = std::ranges::min(w, [](P const& p1, P const& p2){ return p1.q < p2.q; });  // P pmin {1,'c'}*/
	}
	//--------------------------------------------------------//

	/// max
	{
		// max(a, b) → a if (a < b) is false, b otherwise
		// max(a, b, cmp(o,o)→bool) → a if cmp(a,b) is false, b otherwise

		int const a = 2, b = 9;
		int x = std::max(a,b);  // int x = 9
		struct P { int q; char c; };
		P pmax = std::max(P{1,'y'}, P{2,'x'}, [](P p1, P p2){ return p1.q < p2.q; });  // P pmax {2,'x'};

		/// C++ 11
		// max({v1,v2,v3,…}) → largest_value C++11
		// max({v1,v2,v3,…}, cmp(o,o)→bool) → largest_value
		int x = std::max({3,4,b,3,a,8});  // int x = 9

		/// C++ 20
		// ranges::max(range) → largest_value
		// ranges::max(range, cmp(o,o)→bool) → largest_value

		/*std::vector<int> v {7,9,3,5,3,1,4,8};
		auto x = std::ranges::max(v);  // int x = 9
		struct P { int q; char c; };
		std::vector<P> const w {P{1,'c'},P{3,'a'},P{2,'b'}};
		auto pmax = std::ranges::max(w, [](P p1, P p2){ return p1.q < p2.q; });  // P pmax {3,'a'}*/
	}
	//--------------------------------------------------------//

	/// minmax
	{
		/// C++11
		// minmax(a, b) → {smallest,largest}  C++11
		// minmax(a, b, cmp(o,o)→bool) → {smallest,largest}

		// comparison function/object cmp(a,b) must return true if a should be ordered before b

		int a = 2,  b = 9;
		auto p = std::minmax(a,b);  // std::pair<int,int> p {2,9}
		auto min = p.first;  // int min = 2
		auto max = p.second; // int max = 9
		auto [lo,hi] = std::minmax(a,b);  // int lo = 2, hi = 9  C++17


		/// C++11
		// minmax({v1,v2,v3,…}) → {smallest,largest}  C++11
		// minmax({v1,v2,v3,…}, cmp(o,o)→bool) → {smallest,largest}
		auto p = std::minmax({3,0,b,3,a,8});  // std::pair<int,int> p {0,9}
		auto min = p.first;  // int min = 0
		auto max = p.second; // int max = 9
		auto [lo,hi] = std::minmax({3,0,b,3,a,8});  // int lo = 0, hi = 9  C++17

		/// C++20
		/*std::vector<int> v {7,9,3,5,3,1,4,8};
		auto p = std::ranges::minmax(v);  // std::pair<int,int> p {1,9}
		auto [min,max] = std::ranges::minmax(v);
		struct P { int q; char c; };
		std::vector<P> const w {P{3,'a'},P{2,'b'},P{1,'c'}};
		auto [lo,hi] = std::ranges::minmax(w, [](P p1, P p2){ return p1.q < p2.q; });  // P lo {1,'c'}, hi {3,'a'}*/
	}
	//--------------------------------------------------------//

	/// clamp C++ 17
	{
		// clamp(value, lo, hi) → clamped_value
		// clamp(value, lo, hi, cmp(o,o)→bool) → clamped_value
		int a = std::clamp( 8,  1, 5);  // int a =  5
		int b = std::clamp(-4,  1, 5);  // int b =  1
		int c = std::clamp(-4, -2, 5);  // int c = -2

	}
	//--------------------------------------------------------//

	/// min_element
	// min_element(@begin, @end)
	// min_element(@begin, @end, compare(O,O)->bool)
	{
		std::vector<int> v {7,9,3,5,3,2,4,1,8,0};
		// smallest in subrange 
		auto i = min_element(begin(v)+2, begin(v)+7);
		auto min = *i;  // int min = 2
		// smallest in entire vector:
		auto j = min_element(begin(v), end(v));
		std::cout << *j;  // prints '0'
		// index of smallest:
		auto argmin = distance(begin(v), j);  // int argmin = 9
		i = v.erase(i);    // erase 2
		std::cout << *i; // prints '4'


		/// C++ 20
		/*std::vector<int> v {7,9,3,5,3,2,4,1,8,0};
		auto i = std::ranges::min_element(v);
		auto min = *i;  // int min = 0*/
	}
	//--------------------------------------------------------//

	/// max_element
	// max_element(@begin, @end)
	// max_element(@begin, @end, compare(O,O)->bool)
	{
		std::vector<int> v {7,9,3,5,3,2,4,1,8,0};
		// largest in subrange
		auto i = max_element(begin(v)+2, begin(v)+7);
		auto max = *i;  // int max = 5
		// largest in entire vector:
		auto j = max_element(begin(v), end(v));
		std::cout << *j;  // prints '9'
		// index of largest:
		auto argmax = distance(begin(v), j);  // int argmax = 1
		i = v.erase(i);    // erase 5
		std::cout << *i; // prints '3'


		/// C++ 20
		/*std::vector<int> v {7,9,3,5,3,2,4,1,8,0};
		auto i = std::ranges::max_element(v);
		auto max = *i;  // int max = 9*/
	}
	//--------------------------------------------------------//

	/// minmax_element
	// minmax_element(@begin, @end)
	// minmax_element(@begin, @end, compare(O,O)->bool)
	//--------------------------------------------------------//
	{
		/// C++11
		// returns a std::pair of iterators to the smallest and largest elements in the input range;
		std::vector<int> v {7,1,3,5,3,8,6,2,9,0};
		auto p = minmax_element(begin(v)+2, begin(v)+8);
		auto min = *p.first;    // int min = 2
		auto max = *p.second;   // int max = 8
		// swap element values
		std::swap(*p.first,*p.second);// -> 7 1 3 5 3 2 6 8 9 0

		// min & max in entire vector:
		auto pv = minmax_element(begin(v), end(v));
		auto minv = *pv.first;    // int minv = 0
		auto maxv = *pv.second;   // int maxv = 9
		auto [i,j] = minmax_element(begin(v), end(v)); // C++17
		std::cout << *i <<' '<< *j;  // 0 9

		/// C++ 20
		/*std::vector<int> v {7,1,3,5,3,8,6,2,9,0};
		auto [i,j] = std::ranges::minmax_element(v);
		auto min = *i;  // int min = 0
		auto max = *j;  // int max = 9*/
	}
	return 0;
}
