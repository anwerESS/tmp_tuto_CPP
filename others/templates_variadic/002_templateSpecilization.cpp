// Template Specilization
#include <iostream>

using namespace std;

template<typename T>
bool equal(const T& t1, const T& t2) {return t1 == t2;}

template<>
bool equal<float>(const float& t1, const float& t2)
{
	return abs(t1 - t2) < 0.000001f;
}

template<>
bool equal<double>(const double& t1, const double& t2)
{
	return abs(t1 - t2) < 0.00000001f;
}

int main(int argc, char const *argv[])
{

	std::string s1 = "TEST", s2 = "TEST";
	cout << boolalpha <<  equal(s1, s2) << '\n'; // true
	cout << boolalpha <<  equal(2, 2) << '\n'; // true

	float f1 = 0.999999f, f2 = 1.0f;
	cout << boolalpha <<  equal(0.000001f, f2 - f1) << '\n'; // true after template specialization

	double d1 = 0.9999999999, d2 = 1.0;
	cout << boolalpha <<  equal(0.0000000001, d2 - d1) << '\n'; // true after template specialization

	return 0;
}
