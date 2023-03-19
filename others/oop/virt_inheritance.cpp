#include <iostream>

using namespace std;

struct A {
	int a{10};
};

// struct B : virtual public A {
struct B : public A {
	int b; int aa;
	//B(){a=20;}
	B(){B::a=20;}
};

// struct C :  virtual public A {
struct C :  public A {
	int c; int aa;
	// C(){a=30;}
	C(){C::a=30;}

};

struct D : virtual public B, virtual public C {
// struct D :  public B,  public C {
	int b;
	// D(){a=40;}

};

int main(int argc, char const *argv[])
{
	D d;
	// cout << d.a << "\n"; //  error: request for member ‘a’ is ambiguous (without virtual inheritance)

	// cout << d.A::a << '\n';
	cout << d.B::a << '\n'; // 20
	cout << d.C::a << '\n'; // 30
	// cout << d.a << '\n';

	return 0;

}