// It is basically a wrapper which wraps raw pointer and handles the life time of the object for you, means if there is no reference to the pointer it will delete it otherwise it will hold. There are basically three types of smart pointers.
// TYPES:
// 1. unique_ptr
// 2. shared_ptr
// 3. weak_ptr
// And the basic job of smart pointer is, it actually makes sure that we don't have memory leaks.

#include <iostream>

template <typename T>
class SmartPointer
{
private:
	T *pointer;

public:
	explicit SmartPointer(T *pointer) : pointer(pointer) {}
	~SmartPointer()
	{
		delete pointer;
		std::cout << "pointer deleted : " << this << "\n";
	}
	T &operator*() { return *pointer; }
	T * operator -> () { return pointer; }
};

struct Point
{
	int x;
	int y;
	char name;
};

int main(int argc, char const *argv[])
{
	SmartPointer<int> p_int{new int(20)};
	*p_int = 30;
	std::cout << *p_int << '\n'; // 30


	Point *ppoint = new Point{-2, 3, 'A'};
	SmartPointer<Point> p_p (ppoint);
	// std::cout << "Point : " << (*p_p).name // Point : A (-2, 3)
	// 	<<" (" << (*p_p).x
	// 	<< ", " << (*p_p).y
	// 	<< ")\n";
	std::cout << "Point : " << p_p->name // Point : A (-2, 3)
		<<" (" << p_p->x
		<< ", " << p_p->y
		<< ")\n";
	return 0;
}
