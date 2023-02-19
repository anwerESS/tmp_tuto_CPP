////////// Dynamic memory allocation and De-allocation =>	New, delete, New[], delete[]

#include <iostream>

using namespace std;

///////// LOCAL OVERLOADING ///////
class A{
	int x, y, z;
public:
	A(int x=0, int y=0, int z=0):x(x), y(y), z(z){}

	void * operator new(size_t size){
		cout << "SIZE TO ALLOCATE (void * operator new()) ==> " << size << '\n';
		void * p = malloc(size);
		if(!p) { bad_alloc ba; cout << "cannot alloacate!"; throw ba;}
		return p;
	}

	void operator delete (void * p){
		cout << "dealocate obj (void operator delete)!\n";
		free(p);
	}

	void * operator new[](size_t size){
		cout << "SIZE TO ALLOCATE (void * operator new[]()) ==> " << size << '\n';
		void * p = malloc(size);
		if(!p) { bad_alloc ba; cout << "cannot alloacate!"; throw ba;}
		return p;
	}

	void operator delete[] (void * p){
		cout << "dealocate obj (void operator delete[])!\n";
		free(p);
	}
};
///////// GLOABAL OVERLOADING ///////
void * operator new(size_t size){
	cout << "[GLOB OVERLOADING] : SIZE TO ALLOCATE (void * operator new()) ==> " << size << '\n';
	void * p = malloc(size);
	if(!p) { bad_alloc ba; cout << "cannot alloacate!"; throw ba;}
	return p;
}

void operator delete (void * p){
	cout << "[GLOB OVERLOADING] : dealocate obj (void operator delete)!\n";
	free(p);
}



int main(int argc, char const *argv[])
{
	///////// LOCAL OVERLOADING ///////
	A * a = new A(1,2,3); // SIZE TO ALLOCATE (void * operator new()) ==> 12
	delete a; // dealocate obj (void operator delete)!

	A * a2 = new A[4]{{1,2,3},{1,2,3},{1,2,3},{1,2,3}}; // SIZE TO ALLOCATE (void * operator new[]()) ==> 48
	delete[] a2; // dealocate obj (void operator delete[])!


	///////// GLOBAL OVERLOADING ///////
	int * pi = new int(10); // [GLOB OVERLOADING] : SIZE TO ALLOCATE (void * operator new()) ==> 4
	delete pi; // [GLOB OVERLOADING] : dealocate obj (void operator delete)!

	return 0;
}
