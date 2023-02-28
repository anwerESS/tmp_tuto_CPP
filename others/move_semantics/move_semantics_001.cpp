#include<iostream>

using namespace std;

void printVal(const int &&x) {cout << "RVALUE : X[" << &x << "]  = " << x << '\n';} // RVALUE

void printVal(const int &x) {cout << "LVALUE : X[" << &x << "]  = " << x << '\n';} // LVALUE



int main(int argc, char const *argv[])
{
	int i = 5; // 0x7ffd6c8612e4
	cout << &i << '\n';
	printVal(i); // LVALUE : X[0x7ffd6c8612e4]  = 5
	printVal(std::move(i)); // RVALUE : X[0x7ffd6c8612e4]  = 5

	printVal(5); // RVALUE : X[0x7ffcac13f9e4]  = 5

	int arr[] = {11,22,33,44};

	for(auto &&au : {11,22,33,44}) printVal(au);

	return 0;
}