#include <iostream>

struct A{
	A(){printf("CONSTRUCTOR\n");}

	A(A const&){printf("COPY CONSTRUCTOR\n");}
	A(A const&&){printf("MOVE CONSTRUCTOR\n");}
	const A& operator =(const A&) {printf("COPY ASSIGNMENT\n"); return*this;}
	const A& operator =(const A&&){printf("MOVE ASSIGNMENT\n"); return*this;}
};



int main(int argc, char const *argv[])
{
	A a;						// CONSTRUCTOR
	/*----------------------------------------------*/ printf("\n\n");
	A a1(a);					// COPY CONSTRUCTOR
	/*----------------------------------------------*/ printf("\n\n");
	A a2 = a;					// COPY CONSTRUCTOR
	a2 = a1;					// COPY ASSIGNMENT (because already initialized)
	/*----------------------------------------------*/ printf("\n\n");
	A a3(a);					// COPY CONSTRUCTOR
	A a4(std::move(a3)); 		// MOVE CONSTRUCTOR
	A a5 = A(std::move(a3));	// MOVE CONSTRUCTOR
	a5 = A(std::move(a3));		// MOVE ASSIGNMENT
	/*----------------------------------------------*/ printf("\n\n");
	A a6;						// CONSTRUCTOR
	a6 = std::move(a3);			// MOVE ASSIGNMENT
	/*----------------------------------------------*/ printf("\n\n");
	A a7;	 // CONSTRUCTOR
	a7 = A(a);	// CONSTRUCTOR > COPY CONSTRUCTOR > MOVE ASSIGNMENT

	return 0;
}