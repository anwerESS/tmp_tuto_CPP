
#include <iostream>
#include <cstring>

struct String{
	char * data;
	size_t size;

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

	~String(){
		if(data) delete[] data; data = nullptr;
	}

	void printStr(std::string msg ){std::cout << "printStr() << [" << msg << "]  : " << ((data)?data:"") << '\n';}
};

struct Entity {
	String str;
	 Entity(const String& str)
		//  : str(str) // String(const String& str)  {OBJ : 0x7ffed4317a40}
		 : str(str)// or((String&&) str) // String(String&& str)  {OBJ : 0x7ffe416c5c60}
		{
			// this->str = str; // operator= (String&& str)  {OBJ : 0x7ffceb8be950}
			// this->str = std::move(str); // operator= (String&& str)  {OBJ : 0x7ffceb8be950}
	}

	 Entity(const String&& str)
		 : str(std::move(str))// or((String&&) str) // String(String&& str)  {OBJ : 0x7ffe416c5c60}
		{
	}

	 Entity(Entity& e)
		 : str(std::move(e.str))// or((String&&) str) // String(String&& str)  {OBJ : 0x7ffe416c5c60}
		{
	}

	 Entity(Entity&& e)
		 : str(std::move(e.str))// or((String&&) str) // String(String&& str)  {OBJ : 0x7ffe416c5c60}
		{
	}

};

int main(int argc, char const *argv[])
{

	////// TEST COPY/MOVE CONSTRUCTOR ////////
	{
		String s1("STRING ONE"); // [CALL] : String(const char * str)
		String s2(s1); // [CALL] : String(const String& str)

		String s3((String&&)"String THREE"); // [CALL] : String(const char * str)) > String(String&& str) > ~String()
		String s4(std::move(s1)); // [CALL] :  String(String&& str) > ~String()

		// [CALL] : ~String() // destrcution s4
		// [CALL] : ~String() // destrcution s3
		// [CALL] : ~String() // destrcution s2
		// [CALL] : ~String() // destrcution s1
		///////////////////////////////////////////////////////////
		Entity e1("ENTITY ONE"); // String(const char * str) > Entity(const String&& str) > String(const String& str) > ~String()
		Entity e2(e1); // [CALL] : String(const String&& str) > Entity(Entity& e)
		Entity e3(String("ENTITY THREE"));// [CALL] : String(const char * str) > String(String&& str) > Entity(const String& str) > ~String()
		Entity e4(s4); // [CALL] : Entity(const String& str) > String(const String& str)
		Entity e5(std::move(String("ENTITY THREE"))) ;// [CALL] : String(const char * str) > Entity(const String&& str) > String(const String& str) > ~String()
		Entity e6(std::move(s4)); // [CALL] : Entity(const String&& str) > String(const String& str)
		Entity e7(e6); // [CALL] : Entity(Entity& e) > String(String&& other)
		Entity e8(std::move(e6));// [CALL] : Entity(Entity&& e) > String(String&& other)

		// [CALL] : ~String()
		// [CALL] : ~String()
		// [CALL] : ~String()
		// [CALL] : ~String()
		// [CALL] : ~String()
		// [CALL] : ~String()
		// [CALL] : ~String()
		// [CALL] : ~String()
		// [CALL] : ~String()
		// [CALL] : ~String()
		// [CALL] : ~String()
		// [CALL] : ~String()
	}
	////// TEST COPY/MOVE ASSIGNMENT ////////
	{
		String s1 = "AAAA"; // [CALL] : String(const char * str)
		String s2("222222"); // // [CALL] : String(const char * str)
		s2 = std::move(s1); // operator= (String&& other)

		printf("\n\n");

		String s3 = std::move("CCCCC"); // [CALL] : String(const char * str)
		String s4("444444444"); // [CALL] : String(const char * str)
		s4 = std::move(s3); // operator= (String&& other)
		s4 = s4; // operator= (String&& other)

	}
	{
		String s1("AAAAAA"); // String(const char * str)
		String s2; // String(){}
		s1.printStr("S1 before"); // printStr() << [S1 before]  : AAAAAA
		s2.printStr("S2 before"); // printStr() << [S2 before]  :
		s2 = std::move(s1);
		s1.printStr("S1 after"); // printStr() << [S1 after]  :
		s2.printStr("S2 after"); // printStr() << [S2 after]  : AAAAAA

	}


	return 0;
}