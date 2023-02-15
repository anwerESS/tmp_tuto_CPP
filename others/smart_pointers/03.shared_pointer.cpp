// There are few points about it:
// 0. shared_ptr is a smart pointer which can share the ownership of object (managed object).
// 1. Several shared_ptr can point to the same object (managed object).
// 2. It keep a reference count to maintain how many shared_ptr are pointing to the same object.
//    and once last shared_ptr goes out of scope then the managed object gets deleted.
// 3. shared_ptr is threads safe and not thread safe. [what is this??]
//    a. control block is thread safe
//    b. managed object is not
// 4. There are three ways shared_ptr will destroyed managed object.
//    a. If the last shared_ptr goes out of scope.
//    b. If you initialise shared_ptr with some other shared_ptr.
//    c. If you reset shared_ptr.
// 5. Reference count doesn't work when we use reference or pointer of shared_ptr.

#include <iostream>
#include <memory>



struct Point {
	int x;int y; char name;
	Point(int x, int y, char name):x(x), y(y), name(name){}
	~Point(){std::cout << name << " deleted!\n";}
};

int main(int argc, char const *argv[])
{
	// use_count() : Returns the number of shared_ptr objects that share ownership over the same pointer as this object (including it)
	{
		std::shared_ptr<int> p1 = std::make_shared<int>(15);
		auto p2 = p1;
		std::cout << p1.use_count() << '\n'; // 2
		auto &p3 = p1;
		std::cout << p1.use_count() << '\n'; // 2 (still 2 because it is a reference)
		std::cout << "P1 IS "  << (p1.unique()?"":"NOT ") << "UNIQUE\n"; // P1 IS NOT UNIQUE
	}



	return 0;
}
