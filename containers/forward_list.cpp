// 1. This is single linked list what we know from C programming language.
// 2. Why forward_list why not single_list ?
// 3. We should use this class instead of traditional single linked list because
//    a. Well tested
//    b. Bunch of available function
// 4. Few Available Operations
//    operator =, assign, front, empty, max_size, clear, insert_after, emplace_after, reverse, sort, merge
//    splice_after, unique, remove, remove_if, resize

//////// SINCE C++ 11 /////////


#include <forward_list>
#include <iostream>
#include <algorithm> // std::sort

struct greater
{
    template<class T>
    bool operator()(T const &a, T const &b) const { return a < b; }
};

int main(int argc, char const *argv[])
{
	std::forward_list<int> list1 {1,2,2,6,4,8};
	std::forward_list<int> list2 {9,3,8,0};
	std::forward_list<int> list3 {40,10,30,20};

	list3.insert_after(list3.begin(), 7); // 40 7 10 30 20
	list3.insert_after(list3.begin(), {1,2,3}); // 40 1 2 3 7 10 30 20
	list3.insert_after(list3.before_begin(), list2.begin(), std::next(list2.begin(), 2)); // 9 3 40 1 2 3 7 10 30 20
	list3.push_front(100); // 100 9 3 40 1 2 3 7 10 30 20

   list1.splice_after(list1.cbefore_begin(),
								list2, list2.before_begin(),
								std::next(list2.begin(), 2)); // list1{9 3 1 2 2 6 4 8};list2{8 0}

	//list1.splice_after(list1.cbefore_begin(), list2); // to move entire list

	std::cout << "SIZE OF LIST2 : " << std::distance(list2.begin(), list2.end()) << '\n'; // SIZE OF LIST2 : 2

	std::forward_list<int> list4 {1,2,2,6,2,8};
	list4.unique(); // 1 2 6 2 8
	list4.remove(2); // 1 6 8
	list4.remove_if([](int i){return i > 6;}); // 1 6
	list4.resize(5); // 1 6 0 0 0

	std::forward_list<int> list5 {5,1,3};
	std::forward_list<int> list6 {2,4,6};

	list5.sort();
	list6.sort();

	list5.merge(list6); // list5 {1 2 3 4 5 6}; list6 {}


	list5.assign({5,1,3});	// assign can copy data from one type of container to another example set to list
	list6.assign({2,4,6});
	list5.sort(); // 1 3 5
	list6.sort(); // 2 4 6

	list5.merge(list6, greater());

	return 0;
}
