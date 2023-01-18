// 1. This is double linked list what we know from C programming language.
// 2. List is sequence container that allow non-contiguous memory allocation.
// 3. List is faster compared to other sequence containers (vector, forward_list, deque) in terms of
//    insertion, removal and moving elements in any position provided we have the iterator of the position.
// 4. We should use this class instead of traditional double linked list because
//    a. Well tested
//    b. Bunch of available function
// 5. Few Available Operations
//    operator =, assign, front, back, empty, size, max_size, clear, insert, emplace, push_back, pop_back, push_front
//    pop_front, reverse, sort, merge, splice, unique, remove, remove_if, resize.

#include <iostream>
#include <list>

int main(int argc, char const *argv[])
{

//std::list::erase
	std::list<int> mylist {10, 20, 30, 40, 50, 60, 70, 80, 90};
	std::list<int>::iterator it1,it2;

								// 10 20 30 40 50 60 70 80 90
	it1 = it2 = mylist.begin(); // ^^
	advance (it2,6);            // ^                 ^
	++it1;                      //    ^              ^

	it1 = mylist.erase (it1);   // 10 30 40 50 60 70 80 90
								//    ^           ^
	it2 = mylist.erase (it2);   // 10 30 40 50 60 80 90
								//    ^           ^
	++it1;                      //       ^        ^
	--it2;                      //       ^     ^

	mylist.erase (it1,it2);     // 10 30 60 80 90
								//        ^
	return 0;

}