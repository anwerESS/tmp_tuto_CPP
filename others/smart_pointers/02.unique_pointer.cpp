// 0. unique_ptr is a class template.
// 1. unique_ptr is one of the smart pointer provided by c++11 to prevent memory leaks.
// 2. unique_ptr wraps a raw pointer in it, and de-allocates the raw pointer,
//    when unique_ptr object goes out of scope.
// 3. similar to actual pointers we can use arrow and * on the object of unique_ptr,  because it is overloaded in unique_ptr class.
// 4. When exception comes then also it will de-allocate the memory hence no memory leak.
// 5. Not only object we can create array of objects of unique_ptr.


#include <iostream>
#include <memory>


struct Point {
	int x;int y; char name;
	Point(int x, int y, char name):x(x), y(y), name(name){}
	~Point(){std::cout << name << " deleted!\n";}
};

struct PointDeleter{
	int count;
	void operator()(Point * p){
		++count;
		std::cout << "[" << count << "] "<< p->name << "(" << p->x << ", " << p->y << ") will be deleted\n";
		delete p;
	}
};

int main(int argc, char const *argv[])
{
	// get() : Returns the stored pointer
	{
		std::unique_ptr<int> p1 (new int(5));
		std::unique_ptr<int> p2 = std::make_unique<int>(15);
		// std::unique_ptr<int> p3(p2); not allowed
		//std::unique_ptr<int> p3(std::move(p2));
		int * p5 = p2.get();
		int * p6 = p2.get();
		if (p2 != nullptr)
			std::cout << *p2.get() << '\n';	// 15
		//std::cout << *p3.get() << '\n';
		std::cout << *p6 << '\n';		// 15
	}

	// release() : Releases ownership of its stored pointer, by returning its value and replacing it with a null pointer.
	{
		std::unique_ptr<int> p1 (new int(5));
		std::unique_ptr<int> p2(p1.release()); // p1 = null; *p2 = 5
		int * p3 = p2.release(); // p1 = null; p2 = null; *p3=5
		delete p3;
	}

	// reset() : (Reset pointer) Destroys the object currently managed by the unique_ptr (if any) and takes ownership of p.
	{
		std::unique_ptr<int> p1;
		p1.reset(new int(5)); // *p1 = 5
		p1.reset(new int(10)); // *p1 = 10
		p1.reset(); // p1 = null
	}


	// swap() : Exchanges the contents of the unique_ptr object with those of x, transferring ownership of any managed object between them without destroying either.
	{
		std::unique_ptr<int> p1 (new int(10)); // *p1 = 10
		std::unique_ptr<int> p2 (new int(20)); // *p2 = 20
		p1.swap(p2); // *p1 = 20; *p2 = 10
	}

	// get_deleter() : Returns the stored deleter
	{
		std::unique_ptr<Point, PointDeleter> p1( new Point(-1,2,'A'), PointDeleter());
		std::unique_ptr<Point, PointDeleter> p2( new Point(3,1,'B'));


		PointDeleter pDeleter;
		std::unique_ptr<Point, PointDeleter> p3( new Point(-6,5,'C'), pDeleter);
		std::unique_ptr<Point, PointDeleter&> p4( new Point(4,0,'D'), p3.get_deleter());

		/////////// output ///////////
		// [1] D(4, 0) will be deleted
		// D deleted!
		// [2] C(-6, 5) will be deleted
		// C deleted!
		// [1] B(3, 1) will be deleted
		// B deleted!
		// [1] A(-1, 2) will be deleted
		// A deleted!
	}

	return 0;
}
