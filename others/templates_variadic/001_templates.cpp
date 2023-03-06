#include <iostream>
using namespace std;

template <typename T1, typename T2, typename T3>
T3 sum(T1 t1, T2 t2) { return t1 + t2;}

template<typename T, size_t n>
struct MyContainer{
	T data[n];
	T getData(int idx) {if (idx >= n) throw out_of_range("out_of_range!"); return data[idx];}
	void setData(int idx, int val) {if (idx >= n) throw out_of_range("out_of_range!"); data[idx] = val;}
};


int main(int argc, char const *argv[])
{
	// test template function
	cout << sum<float, int, float>(3.2,5) << '\n';	// 8.2
	cout << sum<int, int, float>(3.2,5) << '\n';	// 8
	cout << sum<float, float, int>(3.2,5) << '\n';	// 8

	// test template class
	MyContainer<int, 4> cont;
	try
	{
		cont.setData(0, 0);
		cont.setData(1, 10);
		cont.setData(2, 20);
		cont.setData(3, 30);
		cont.setData(4, 40); // throw exception
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';	// "out_of_range!")
	}

	try
	{
		for(int i = 0; i < 5; ++i)
			cout << "data[" << i << "] : " << cont.getData(i) << '\n';
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n'; // "out_of_range!")
	}

	return 0;
}
