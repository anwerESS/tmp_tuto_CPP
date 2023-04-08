#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class String{
	char * data;
	size_t size;
public:
	String(){}

	String(const String& str){ // copy constructor
		this->size = str.size;
		this->data = new char[size + 1];
		memcpy(this->data, str.data, size + 1);
	}

	String(String&& other){ // move constructor
		this->size = other.size;
		this->data = other.data;
		other.size = 0;
		other.data = nullptr;
	}

	String&  operator= (const String& other){ // copy assignment
		if(this != &other){ // obj = obj
			delete[] data; // mandatory (memory leak)
			this->size = other.size;
			this->data = new char[size + 1];
			memcpy(this->data, other.data, size + 1);
		}
		return *this;
	}

	String&  operator= (String&& other){ // move assignment
		if(this != &other){ // // obj = std::move(obj)
			delete[] data; // mandatory (memory leak)
			this->size = other.size;
			this->data = other.data;
			other.size = 0;
			other.data = nullptr;
		}
		return *this;
	}

	String(const char * str){
		size = strlen(str);
		data = new char[size + 1];
		memcpy(data, str, size + 1);
	}

	virtual ~String(){ std::cout <<"DESTRUCTOR String\n";
		if(data) delete[] data; data = nullptr;
	}

	void printStr(std::string msg ){std::cout << "printStr() << [" << msg << "]  : " << ((data)?data:"") << '\n';}
};

class ChildString : public String {
	int XX;
public:
	ChildString(const char * str) : String(str){}
	~ChildString(){std::cout <<"DESTRUCTOR ChildString \n";}
};



int main(int argc, char const *argv[])
{

	String * ch_str = new ChildString("MY CHILD STRING");
	ch_str->printStr("");
	delete ch_str;
	/////////// output /////////
	// printStr() << []  : MY CHILD STRING
	// DESTRUCTOR ChildString 
	// DESTRUCTOR String
	///////////////////////////
	return 0;
}
