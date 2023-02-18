// Implicit conversion
// Explicit conversion
// 		c-style
// 		static_cast
// 		dynamic_cast
// 		const_cast
// 		reinterpret_cast


#include <iostream>
#include <string>




int main(int argc, char const *argv[])
{
	/////////// Implicit conversion ///////////
	{
		int a = 12; char c = 'A';
		std::cout << a + c << '\n'; // 77 (12 + 65)

		// class A {};
		// class B { public: B (A a) {} };

		// A a;
		// B b=a;
	}

	/////////// Explicit conversion ///////////
	// c-style & functional notation
	{
		short s=2000;
		int i;
		i = (int) s;    // c-like cast notation
		i = int (s);    // functional notation

		struct A{int x, y;};
		struct B {
			int i,j;
			B(int i, int j):i(i), j(j){}
			int result(){return i + j;}
		};

		A a{3,5};
		B * b = (B*)&a;
		int res =b->result();
		std::cout << res << '\n';	// 8
	}
	//-------------------------------------------------------------------------//
	// static_cast
	{
		/// prevent dangerous cast -- more restrictive
		char c = 'A';
		int * p1 = (int*)&c;
		*p1 = 3; // pass at compile time and fail at run time
		// int * p2 = static_cast<int*>(&c); // compile time error


		/// conversion constructor & conversion operator
		struct A{
			int i;
			A(int i):i(i){std::cout<<"CONVERSION CONSTRUCTOR\n";}
			operator std::string(){std::cout<<"CONVERSION OPERATOR\n"; return std::to_string(i);}
		};

		A a(123); // CONVERSION CONSTRUCTOR
		std::string s1 = a; // CONVERSION OPERATOR // alowed but not readable
		std::cout<< "S1 = " << s1 << '\n'; // S1 = 123

		a = static_cast<A>(456); // CONVERSION CONSTRUCTOR
		std::string s2 = static_cast<std::string>(a); // CONVERSION OPERATOR
		std::cout<< "S2 = " << s2 << '\n'; // S1 = 123


		/// converting from void* or to void*
		int myInt = 10;
		void * p_myInt_void = static_cast<void*>(&myInt);
		int * p_myInt_int = static_cast<int*>(p_myInt_void);

		/// conversion involving inheritance : is-a (below an example of private inheritance)
		class C{}; class D: private C{};

		D d;
		C * a_ptr = (C*) &d; // allowed
		// C * a_ptr = static_cast<C*>(&d); // conversion to inaccessible base class "C" is not allowed

	}
	//-------------------------------------------------------------------------//
	// dynamic_cast
	// • On success returns a value of new_type
	// • On failure:
	// 		➢ If new_type is pointer 4 null pointer
	// 		➢ If new_type is reference 4 bad_cast exception
	{
		// dynamic_cast can be used only with pointers and references to objects. Its purpose is to ensure that the result of the type conversion is a valid complete object of the requested class.
		// Therefore, dynamic_cast is always successful when we cast a class to one of its base classes:
		// The second conversion in this piece of code would produce a compilation error since base-to-derived conversions are not allowed with dynamic_cast unless the base class is polymorphic.
		{
			class CBase { };
			class CDerived: public CBase { };

			CBase b; CBase* pb;
			CDerived d; CDerived* pd;

			pb = dynamic_cast<CBase*>(&d);     // ok: derived-to-base
			// pd = dynamic_cast<CDerived*>(&b);  // wrong: base-to-derived
		}

		// When a class is polymorphic, dynamic_cast performs a special checking during runtime to ensure that the expression yields a valid complete object of the requested class:
		{
			class CBase { virtual void dummy() {} };
			class CDerived: public CBase { int a; };

			try {
					CBase * pba = new CDerived;
					CBase * pbb = new CBase;
					CDerived * pd;

					pd = dynamic_cast<CDerived*>(pba);
					if (pd==0) std::cout << "Null pointer on first type-cast\n"; // OK

					pd = dynamic_cast<CDerived*>(pbb);
					if (pd==0) std::cout << "Null pointer on second type-castn\n"; // Null pointer on second type-castn
				} catch (std::exception& e) {std::cout << "Exception: " << e.what();}
		}


		/// example: references
		{
			class Base {virtual void f(){}};
			class Derived : public Base {};

			Derived d;
			Base b;
			try {
				Base &rb = dynamic_cast<Base &>(d);
				Derived &rd = dynamic_cast<Derived &>(b); // Exception bad cast
			} catch(std::exception& e){ std::cout <<  e.what() << '\n';}
		}
	}
	//-------------------------------------------------------------------------//
	// const_cast
	{
		// passing const data to a func that doesn't receive const
		{
			auto print = [](char * str){std::cout << str << '\n';};
			const char * c = "sample text";
			print ( const_cast<char *> (c) );
		}

		// change non-const class member inside a const member function
		{
			struct A {
				int x;
				void f(int i) const{
					// this->x = i; // ERROR
					const_cast<A*>(this)->x = i;
				}
			};
		}

		// undefined behaviour to modify a value initially declares as const
		{
			const int a1 = 10;
			const int * p1 = &a1;
			// int * p2 = p1; // ERROR
			int * p2 = const_cast<int*>(p1);
			*p2 = 11;
			std::cout << a1 <<'\n'; // still 10 due to compiler optimization

			const volatile int x = 20;
			int &y = const_cast<int&>(x);
			y = 30;
			std::cout << x <<'\n';
		}
	}
	//-------------------------------------------------------------------------//
	/// reinterpret_cast : Inherently unsafe conversions (cannot convert const and volatile varialbles)
	// • The reinterpret_cast operator can be used for conversions such as: o char* to int*, or o One class* to Unrelated class*, 41— which are inherently unsafe
	// • The result of a reinterpret_cast cannot safely be used for anything other than being cast back to its original type. Other uses are at best non•ortable.
	{
		struct A {
			int x1, x2;
			A():x1(10), x2(30){}
			void printA(){printf("X1 = %d\t X2 = %d\n", x1, x2);}
		};

		struct B {
			char c;
			B():c('A'){}
			void printB(){printf("c = %d\n", c);}
		};

		// type to another type
		int a1 = 70; // A -> 65
		int * p1 = &a1;
		char *pc = reinterpret_cast<char*>(p1);
		std::cout << *pc << '\n'; // F

		// ptr to non ptr
		int * p2 = reinterpret_cast<int*>(a1);
		std::cout << p2 << '\n'; // 0x46
		std::cout << reinterpret_cast<long>(p2) << '\n'; // 70

		// One class* to Unrelated class*
		A a; B b;
		A *pA = reinterpret_cast<A*>(&b);
		B *pB = reinterpret_cast<B*>(&a);
		pA->printA(); // X1 = -889700031  X2 = 8388334
		pB->printB(); // c = 10
		A * pA1 = reinterpret_cast<A*>(pB);
		B * pB1 = reinterpret_cast<B*>(pA);
		pA1->printA(); // X1 = 10  X2 = 30
		pB1->printB(); // c = 65

		// working with bits
		struct S1 {int x; int y;};
		struct S2 {char c1; char c2;};

		S1 s1{0x01020304};
		S2 * p_s2 = reinterpret_cast<S2*>(&s1);
		std::cout << (int)p_s2->c1 << '\n'; // 0x04
		std::cout << (int)p_s2->c2 << '\n';	// 0x03
	}
	//-------------------------------------------------------------------------//
	// typeid : allows to check the type of an expression:
	{
		int * a,b;
		a=0; b=0;
		if (typeid(a) != typeid(b))
		{
			std::cout << "a and b are of different types:\n"; // a and b are of different types:
			std::cout << "a is: " << typeid(a).name() << '\n'; // a and b are of different types:
			std::cout << "b is: " << typeid(b).name() << '\n'; // b is: i
		}
	}











}

//// private Inheritance : Not is-a but has a

// #include <iostream>

// class Person{};
// class Student: private Person{}; // priavte

// void eat(const Person& p){} // anyone cant eat
// void study(const Student& s){} // only students study

// int main()
// {
// 	Person p; // p is a Person
// 	Student s; // s is a Student
// 	eat(p);
// 	eat(s); // conversion to inaccessible base class "Person" is not allowed
// 	return 0;
// }