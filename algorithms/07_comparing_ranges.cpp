/// https://hackingcpp.com/cpp/std/algorithms/comparing_ranges.html

// equal
// mismatch → {@in1,@in2}
// lexicographical_compare
// lexicographical_compare_three_way C++20

#include <iostream>
#include <vector>

int main(int argc, char const *argv[])
{
	// equal
	{
		// equal(@begin1, @end1, ,@begin2)
		// equal(@begin1, @end1, ,@begin2, @end2)
		//uses operator == for comparing elements; alternatively a custom function(object) can be passed as additional argument
		std::vector<int> r1 {0,1,2,3,4,5,6,7,8,9};
		std::vector<int> r2 {1,2,3,4,5,6,0,0};
		std::cout << equal(begin(r1)+2, begin(r1)+7, begin(r2)+1);  // true
		// compare entire containers:
		std::cout << equal(begin(r1), end(r1), begin(r2));  // false
		// compare other subranges:
		std::cout << equal(begin(r1)+1, begin(r1)+7, begin(r2), begin(r2)+6);  // true
		// custom type
		struct P { int x; char q; };
		std::vector<P> a { P{1,'n'}, P{2,'m'} };
		std::vector<P> b { P{1,'y'}, P{2,'z'} };
		// compare 'P's only by member 'x'
		std::cout << equal(begin(a),end(a), begin(b),end(b), [](P p1, P p2) {return p1.x == p2.x; } );  // true

		// C++20
		// equal(range1, range2)
		/*std::vector<int> range1 {2,3,4,5,6};
		std::vector<int> range2 {2,3,4,5,6};
		cout << std::ranges::equal(range1, range2);  // true*/
	}

	// mismatch
	{
		// mismatch(@begin1, @end1, ,@begin2) -> @mismatch1 and @mismatch2
		// mismatch(@begin1, @end1, ,@begin2, @end2)
		// returns a std::pair of iterators to the first mismatching elements in 2 ranges
		// uses operator == for comparing elements; alternatively a custom function(object) can be passed as additional argument
		std::vector<int> r1 {0,1,2,3,4,5,6,7,8,9};
		std::vector<int> r2 {1,2,3,4,5,7,8,8};
		auto p = mismatch(begin(r1)+2, begin(r1)+9, begin(r2)+1);
		// != end-of-range ⇒ mismatch
		if (p.first  != begin(r1)+9) { auto p1value = *p.first;  }  // 6
		if (p.second != end(r2))     { auto p2value = *p.second; }  // 7
		// compare entire containers:
		auto q = mismatch(begin(r1), end(r1), begin(r2));
		if (q.first != end(r1)) {
			auto q1value = *q.first;  // 0
			auto q1index = distance(begin(r1), q.first);  // 0
		}
		if (q.second != end(r2)) {
			auto q2value = *q.second;  // 1
			auto q2index = distance(begin(r2), q.second);  // 0
		}

		// C++20
		// mismatch(range1, range2)
		/*std::vector<int> range1 {1,5,4,6,3};
		std::vector<int> range2 {1,5,4,7,3};
		auto [p1,p2] = std::ranges::mismatch(range1, range2);
		auto const value1 = *p1;  // 6
		auto const value2 = *p2;  // 7*/
	}

	// lexicographical_compare
	{
		// lexicographical_compare(@begin1, @end1, ,@begin2, @end2)
		std::string r1 = "xalgori";
		std::string r2 = "abced";
		std::cout << lexicographical_compare(begin(r1)+1, begin(r1)+5,
							begin(r2)+1, begin(r2)+4);  // true (r1 before r2)
		// compare entire containers:
		std::cout << lexicographical_compare(begin(r1), end(r1),
							begin(r2), end(r2));  // false (r1 after r2)
		// strings are actually already comparable:
		std::cout << (r1 < r2);  // false
		std::cout << (r1 > r2);  // true (r1 after r2)

		// custom type
		struct P { int x; int y; };
		std::vector<P> a { P{1,9}, P{2,9} };
		std::vector<P> b { P{1,8}, P{3,8} };
		// compare 'P's only by member 'x'
		std::cout << lexicographical_compare(begin(a),end(a), begin(b),end(b), 
		[](P p1, P p2) { return p1.x < p2.x; } );  // true

		// C++ 20
		// lexicographical_compare(range1, range2)
		/*std::vector<char> range1 = {'a','l','g','o'};
		std::vector<char> range2 = {'b','c','e'};
		cout << std::ranges::lexicographical_compare(range1, range2);  // true
		cout << std::ranges::lexicographical_compare(range1, range2, std::greater<>{});  // false*/
	}

	// lexicographical_compare_three_way (C++20)
	// lexicographical_compare_three_way(@begin1, @end1, ,@begin2, @end2)
	// result:
	// 		< 0 ==> range1 before range2
	// 		= 0 ==> range1 equiv to  range2
	// 		> 0 ==> range1 after range2
	// compares two ranges using 3-way comparisons and returns the result as a value of the strongest applicable comparison category (std::::strong_ordering, std::::weak_ordering or std::::partial_ordering)
	{
		/*std::string r1 = "xalgori";
		std::string r2 = "abced";
		auto const lcA = lexicographical_compare_three_way(
		begin(r1)+1, begin(r1)+5, begin(r2)+1, begin(r2)+4);
		cout << (lcA <  0);  // true
		cout << (lcA == 0);  // false
		cout << (lcA >  0);  // false
		// compare entire strings with C++20's 'spaceship' operator:
		auto const lcB = r1 <=> r2;
		cout << (lcB <  0);  // false
		cout << (lcB == 0);  // false
		cout << (lcB >  0);  // true*/
	}

	return 0;
}


