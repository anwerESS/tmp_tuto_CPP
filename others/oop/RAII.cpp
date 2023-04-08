// Resource Acquisition is Initialization (RAII)
// https://en.cppreference.com/w/cpp/language/raii
// https://www.tomdalling.com/blog/software-design/resource-acquisition-is-initialisation-raii-explained/
// http://guillaume.belz.free.fr/doku.php?id=pourquoi_le_raii_est_fondamental_en_c
// https://blog.stratifylabs.dev/device/2020-12-22-RAII-Everywhere-in-Cpp/


#include <iostream>
#include <stdexcept>


//////// C Lib ///////
char * g_ptr;
void mylib_init(){ g_ptr = (char*)malloc(1024);printf("mylib_init\n");}
int mylib_print(){printf("TEST MY C LIBBRARY\n"); static int i; return ++i;}
void mylib_cleanup(){free(g_ptr); printf("mylib_cleanup\n");}
/////////////////////

//////// C++ CLASS WRAPPER ////////
class MyClassWrapper{
	public:
	MyClassWrapper(){mylib_init();}
	~MyClassWrapper(){mylib_cleanup();}

	void someOperation(){ if(mylib_print() == 2) throw  std::runtime_error("THROW EXEPTION");}
};
/////////////////////




int main(int argc, char const *argv[])
{

	//////////////////// USING RAII ////////////////
	MyClassWrapper myWapper;

	try
	{
		for (size_t i = 0; i < 5; i++)
		{
			myWapper.someOperation();
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}


	return 0;
}
