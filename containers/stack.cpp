// 0. std::stack class is a container adapter that gives the programmer the functionality of a stack.
// 1. Internally it uses std::deque STL container.
// 2. It is LIFO (last-in, first-out) data structure.
// 4. std::stack allows to push(insert) and pop(remove) only from back.

// FUNCTIONS PROVIDED:
// empty() – Returns whether the stack is empty – Time Complexity : O(1)
// size() – Returns the size of the stack – Time Complexity : O(1)
// top() – Returns a reference to the top most element of the stack – Time Complexity : O(1)
// push(g) – Adds the element ‘g’ at the top of the stack – Time Complexity : O(1)
// pop() – Deletes the top most element of the stack – Time Complexity : O(1)

#include <iostream>
#include <stack>

int main(int argc, char const *argv[])
{
	std::stack<int> mystack;
	mystack.push(1);
	mystack.push(2);
	mystack.push(3);

	std::cout << "TOP : " << mystack.top() << '\n'; // TOP : 3

	mystack.pop();

	std::cout << "SIZE : " << mystack.size() << '\n'; // SIZE : 2

	return 0;
}
