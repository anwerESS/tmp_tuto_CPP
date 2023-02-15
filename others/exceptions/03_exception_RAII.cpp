// http://guillaume.belz.free.fr/doku.php?id=pourquoi_le_raii_est_fondamental_en_c#:~:text=Le%20RAII%20(%E2%80%9CRessource%20Acquisition%20Is,exception%20qui%20emp%C3%AAche%20la%20lib%C3%A9ration.
// https://nodatek.com/article10/tuto-cpp-le-raii

#include <iostream>

class MyClass{
	int * arr;
public:
	void allocate(){arr = new int[100];	}
	void cleanup(){std::cout << "cleanup()" << '\n'; if (arr) {delete [] arr; arr = nullptr;}}

	~MyClass(){std::cout << "~MyClass()" << '\n'; cleanup();}
};


int main(int argc, char const *argv[])
{
	MyClass myClass;
	try{ // no memory leak possible
		myClass.allocate();
		throw std::runtime_error("");
	} catch(...){

	}

	std::cout << "\n------- END OF MAIN ----------\n";


	return 0;
}
