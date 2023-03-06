#include <iostream>
#include <memory>
#include <vector>

using namespace std;

template<typename T, size_t N = 10>
class MyContainer{
	size_t m_size;
	T * m_data;
public:
	MyContainer():m_size(N),m_data(new T[N]){nbr_instance++;}
	~MyContainer(){delete[] m_data;}

	void setVal(int idx, const T& val){m_data[idx] = val;}
	T getVal(int idx){return m_data[idx];}

	static int nbr_instance;
};

template<typename T, size_t N> int MyContainer<T, N>::nbr_instance; // tell compiler that it exists
// template<typename T, size_t N> int MyContainer<T, N>::nbr_instance = 0; // tell compiler that it exists


// Class template argument deduction (CTAD)
#if __cplusplus >  201703L
template<typename first, typename second>
struct Entry{
	first key; second value;
	Entry(first key, second value):key(key), value(value){};
};
#endif

int main(int argc, char const *argv[])
{
	MyContainer<int, 5> cont_int1;
	MyContainer<int, 5> cont_int2;
	MyContainer<int, 3> cont_int3;
	MyContainer<float, 5> cont_float;

	std::cout << "nbr of instances : " << MyContainer<int, 5> ::nbr_instance << '\n'; // nbr of instances : 2
	std::cout << "nbr of instances : " << MyContainer<int, 3> ::nbr_instance << '\n'; // nbr of instances : 1
	std::cout << "nbr of instances : " << MyContainer<float, 5> ::nbr_instance << '\n'; // nbr of instances : 1


	// CTAD
#if __cplusplus >  201703L
	std::vector v1{1,2,3,4}; // alowed since c++17

	Entry entry_1 (1, 10);
	Entry <int, int>  entry_2(2, 20);
	Entry entry_3 ("key3", 10.1);

	std::cout << "" << entry_3.key << " = " << entry_3.value << '\n'; // key3 = 10.1
#endif

	return 0;
}
