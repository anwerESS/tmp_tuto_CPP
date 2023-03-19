// Lambda Capture List
// The following table shows different use cases for the same:

// [ ] ( ) { }	no captures
// [=] ( ) { }	captures everything by copy(not recommendded)
// [&] ( ) { }	captures everything by reference(not recommendded)
// [x] ( ) { }	captures x by copy
// [&x] ( ) { }	captures x by reference
// [&, x] ( ) { }	captures x by copy, everything else by reference
// [=, &x] ( ) { }	captures x by reference, everything else by copy

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
void printVect(const T& t){for(const auto& it : t){cout << it << ' ';} cout << '\n';}

class MyClass {
public:
	MyClass(int value) : m_value(value) {}

	void printValue() {
		m_value = -1;
		auto lambda1 = [this]() { m_value = 10; cout << "INSIDE LAMBDA1 :" << m_value  << '\n';};
		lambda1(); // BEFORE LAMBDA1 :10
		cout << "BEFORE LAMBDA1 :" << m_value  << '\n'; // INSIDE LAMBDA1 :10
		cout << "AFTER LAMBDA1 :" << m_value << '\n'; // AFTER LAMBDA1 :10

		m_value = -2;
		auto lambda2 = [*this]() mutable { m_value = 20; cout << "INSIDE LAMBDA2 :" << m_value  << '\n';};
		cout << "BEFORE LAMBDA2 :" << m_value  << '\n'; // BEFORE LAMBDA2 :-2
		lambda2(); // INSIDE LAMBDA2 :20
		cout << "AFTER LAMBDA2 :" << m_value << '\n'; // AFTER LAMBDA2 :-2
	}

private:
	int m_value;
};

int main(int argc, char const *argv[])
{
	int i = -1; int j = -2;
	std::vector<int> v{10, 20 ,30 ,40, 50};
	printVect(v); // 10 20 30 40 50

	std::for_each(v.begin(), v.end(), [](auto au){ au /= 10;});
	printVect(v); // 10 20 30 40 50

	std::for_each(v.begin(), v.end(), [&](auto& au){ au /= 10;});
	printVect(v); // 1 2 3 4 5

	//capture i by refrence and j by value
	std::for_each(v.begin(), v.end(), [&i, j](auto& au){ au /= 10; i = j;});
	printVect(v); // 1 2 3 4 5
	cout << "i = " << i << '\n'; // -2


	// capture i and j by value
	/* the mutable keyword can be used in lambda functions to indicate that the lambda function can modify the captured variables even if they are captured by value*/
	/*Finally, outside the lambda function,i and j were not modified by the lambda function.*/
	i = -1; j = -2;
	std::for_each(v.begin(), v.end(), [i,j]  (auto& au) mutable{ au /= 10; i = j = au;});
	printVect(v); // 1 2 3 4 5
	cout << "i = " << i << '\n';	//-1
	cout << "j = " << j << '\n';   // -2


	///////// TEST MYCLASS /////
	MyClass obj(42);
    obj.printValue();


	return 0;
}