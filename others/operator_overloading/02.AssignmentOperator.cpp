////////// Assignment operator
#include <iostream>
#include <cstring>

struct B{
	int val;
	friend class A;
};

class A{
	int * val;
public:
	A(){}
	A(int i):val(new int){}
	void setVal(int i){delete val; val = new int(i); }
	void printA(){std::cout << "VAL : " << *val << '\n';}
	// Assignment operator  =>	=, +=,*=, /=,-=, %=
	A operator=(const A& rhs){
		delete val;
		val = new int(*rhs.val);
		return *this;
	}

	A operator=(const B& rhs){
		delete val;
		val = new int(rhs.val);
		return *this;
	}

};


int main(int argc, char const *argv[])
{
	A a1(10);
	A a2;
	a2 = a1;
	a1.setVal(20);
	a1.printA();
	a2.printA();

	B b{30};
	a1 = b;
	a1.printA();

	return 0;
}
