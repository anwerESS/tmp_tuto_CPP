// 0. std::queue class is a container adapter that gives the programmer the functionality of a queue
// 1. queue is FIFO (first-in, first-out) data structure.
// 2. std::queue provides only specific set of functions.
// 3. std::queue allows to push(insert) at back and pop(remove) from front.
// 4. std::queue gives front, back, push, pop, empty, size.

#include <iostream>
#include <queue>

int main(int argc, char const *argv[])
{
	std::queue<int> myqueue;



	myqueue.push(1);
	myqueue.push(2);
	myqueue.push(3);

	std::cout << "BACK : " << myqueue.back() << '\n'; // BACK : 3
    std::cout << "FRONT : " << myqueue.front() << '\n'; // FRONT : 1

	while (!myqueue.empty())
	{
		myqueue.pop();
		std::cout << "SIZE : " << myqueue.size() << '\n';
	}

	///// output /////
	// SIZE : 2
	// SIZE : 1
	// SIZE : 0
	////////////



	return 0;
}
