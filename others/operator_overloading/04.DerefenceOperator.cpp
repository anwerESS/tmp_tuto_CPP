#include <iostream>

using namespace std;

struct Point{int x, y; /**/	void printItem(){cout << "P(" << x << ',' << y << ")\n";} };

template<typename T>
class XWrapper{
	T * item;
public:
	XWrapper(T * p):item(p){}
	~XWrapper(){delete item;}

	void printItem(){item->printItem();}
	// De-referencing  => -> *
	T * operator -> (){cout << "CALL : T * operator -> ()\n"; return item;}
	T& operator *(){cout << "CALL : T& operator *()\n"; return *item;}

};



int main(int argc, char const *argv[])
{
	XWrapper<Point>  wrapper(new Point{5,10});

	int& x = wrapper->x; // CALL : T * operator -> ()
	x = 25;
	wrapper.printItem(); // P(25,10)

	Point& p1 = *wrapper; // CALL : T& operator *()
	p1.y = 35;
	wrapper.printItem(); // P(25,10)

	return 0;
}
