// 1. std::array is a container that encapsulates fixed size arrays.
// 2. array size is needed at compile time.
// 3. Assign by value is actually by value.
// 4. Access Elements:
//    a. at()
//    b. []
//    c. front()
//    d. back()
//    e. data() // gives access to the underlying array

#include <iostream>
#include <array>

int main()
{
	std::array<int, 10> myarray;
	std::array<int, 5> myarray2 {10, 20, 30, 40, 50};
	std::array<int, 5> myarray3 = {11, 22, 33, 44, 55};

	myarray.fill(5);

	// assign some values:
	for (int i = 0; i < 10; i++)
		myarray.at(i) = i + 1;

	// print content:
	std::cout << "myarray contains:";
	for (int i = 0; i < 10; i++)
		std::cout << ' ' << myarray.at(i);

	for (auto a : myarray2)
		std::cout << a;

	std::cout << '\n';

	return 0;
}