// https://hackingcpp.com/cpp/lang/exceptions.html


#include <iostream>
#include <array>
#include <vector>


void test()  throw(int) // throw()  deprecated C++11 no longer available in c++17 (use noexcpt instaed)
{
		//throw(std::string("STRING EXCEPTION"));
		// throw("CHAR * EXCEPTION");
		throw(99);
		// throw(std::runtime_error("MY RUNTIME ERROR"));
		//throw(float()); // -> catch(...)
}


int main(int argc, char const *argv[])
{

	//------------------------------------------------------------//
	try
	{
		//throw(std::string("STRING EXCEPTION"));
		// throw("CHAR * EXCEPTION");
		//throw(99);
		// throw(std::runtime_error("MY RUNTIME ERROR"));
		throw(float()); // -> catch(...)
	}
	catch(std::string)	{std::cout << "throw(std::string(\"STRING EXCEPTION\"))" << '\n';}
	catch(const char * str)	{std::cout << "throw(\"CHAR * EXCEPTION\")" << '\n';}
	catch(int i)	{std::cout << "throw(99)" << '\n';}
	catch(const std::exception& e)
	{
		std::cout << "	catch(const std::exception& e)" << '\n';
		std::cerr << e.what() << '\n';
	}
	catch(...){std::cout << "catch(...)" << '\n';}
	//------------------------------------------------------------//

	try
	{
		test();
	}
	catch(std::string)	{std::cout << "throw(std::string(\"STRING EXCEPTION\"))" << '\n';}
	catch(const char * str)	{std::cout << "throw(\"CHAR * EXCEPTION\")" << '\n';}
	catch(int i)	{std::cout << "throw(99)" << '\n';}
	catch(const std::exception& e)
	{
		std::cout << "	catch(const std::exception& e)" << '\n';
		std::cerr << e.what() << '\n';
	}
	catch(...){std::cout << "catch(...)" << '\n';}
	//

	// std::cout << "\n------------- END ------------\n"<< '\n';
	//------------------------------------------------------------//
	{
		std::vector<int> v {0,1,2,3,4};
		// narrow contract: no checks, max performance
		int a = v[6];     //  UNDEFINED BEHAVIOR
		// wide contract: checks if out of bounds
		int b = v.at(6);  // throws std::out_of_range
	}
	//------------------------------------------------------------//

	return 0;
}
