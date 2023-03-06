#include <iostream>

using namespace std;

template<typename T> T Sum(T t1){return t1;}

template<typename T, typename ...Args>
T Sum(T first, Args ...args)
{
	return first + Sum(args...);
	// return first + Sum(T(args)...); Sum<double, double>(1.4, 2, 3, 4.3, 5) ==> 15.7
}

template<typename T1, typename T2>
auto Multiply(T1 t1, T2 t2) ->decltype(t1*t2)
{
	float f;
	return t1 * t2;
}

int main(int argc, char const *argv[])
{
	cout << Sum(1, 2, 3, 4.1, 5) << '\n' ;	// 15  !!
	cout << Sum(1.4, 2, 3, 4.3, 5) << '\n' ;	// 15.4 !!
	cout << Sum<double>(1.4, 2, 3, 4.3, 5) << '\n' ;	// 15.4 !!
	cout << Sum<double, double>(1.4, 2, 3, 4.3, 5) << '\n' ;	// 15.4 !!

	cout << Multiply(3.05, 5) << '\n' ;	// 15.25 !!
	cout << Multiply(2, 5.05) << '\n' ;	// 15.1 !!

	return 0;
;}
