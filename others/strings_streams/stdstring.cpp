// https://cplusplus.com/reference/string/
// https://cplusplus.com/reference/string/basic_string/

// https://hackingcpp.com/cpp/std/string_basics.html


// Convert from strings
//		stoi	: Convert string to integer (function template)
//		stol	: Convert string to long int (function template)
//		stoul	: Convert string to unsigned integer (function template)
//		stoll	: Convert string to long long (function template)
//		stoull	: Convert string to unsigned long long (function template)
//		stof	: Convert string to float (function template)
//		stod	: Convert string to double (function template)
//		stold	: Convert string to long double (function template)

// Convert to strings
//		to_string	: Convert numerical value to string (function)
//		to_wstring	: Convert numerical value to wide string (function)


// Capacity:
//		size			: Return size (public member function)
//		length			: Return length of string (public member function)
//		max_size		: Return maximum size (public member function)
//		resize			: Resize string (public member function)
//		capacity		: Return size of allocated storage (public member function)
//		reserve			: Request a change in capacity (public member function)
//		clear			: Clear string (public member function)
//		empty			: Test whether string is empty (public member function)
//		shrink_to_fit	: Shrink to fit (public member function)

// Element access:
//		operator[]	: Get character of string (public member function)
//		at			: Get character of string (public member function)
//		back		: Access last character (public member function)
//		front		: Access first character (public member function)

// Modifiers:
//		operator+=	: Append to string (public member function)
//		append		: Append to string (public member function)
//		push_back	: Append character to string (public member function)
//		assign		: Assign content to string (public member function)
//		insert		: Insert into string (public member function)
//		erase		: Erase characters from string (public member function)
//		replace		: Replace portion of string (public member function)
//		swap		: Swap string values (public member function)
//		pop_back	: Delete last character (public member function)

// String operations:
//		c_str				: Get C-string equivalent
//		data				: Get string data (public member function)
//		get_allocator		: Get allocator (public member function)
//		copy				: Copy sequence of characters from string (public member function)
//		find				: Find first occurrence in string (public member function)
//		rfind				: Find last occurrence in string (public member function)
//		find_first_of		: Find character in string (public member function)
//		find_last_of		: Find character in string from the end (public member function)
//		find_first_not_of	: Find non-matching character in string (public member function)
//		find_last_not_of	: Find non-matching character in string from the end (public member function)
//		substr				: Generate substring (public member function)
//		compare 			: Compare strings (public member function)


#include <iostream>
#include <algorithm>



int main(int argc, char const *argv[])
{
	/// std::string Manipulation
	{
		// insert
		{
			std::string s1 = "ABEF";
			std::string s2 = "xxCDxx";
			auto it = s1.insert(s1.begin()+2, s2.begin()+2, s2.begin()+4); // s1 = "ABCDEF"; it -> 'C'
			auto ret = s1.insert(0, "XY"); // ret = s1 = "XYABCDEF"
		}
		// append
		{
			std::string s1 = "ABEF";
			std::string s2 = "xxCDxx";
			s1.append(s2); // s1 = "ABEFxxCDxx"
			// s1.append(s2, 3); // s1 = "ABEFDxx"
			// s1.append(s2, 3, 1);// s1 = "ABEFD"
		}
		// erase
		{
			std::string s1 = "0123456789";
			std::string s3 = s1.erase(4,2); // s1 = "01236789"; s3 =s1
			s1 = "0123456789";
			s1.erase(s1.begin()+ 4, s1.end() - 4); // s1 = "01236789"
		}
		// replace
		{
			std::string s1 = "ABCDEFGHI", s2 = "012345";
			s1.replace(3,2, "0123456", 2, 3); //ABC234EFGHI
			s1 =  "ABCDEFGHI";
			s1.replace(s1.begin()+3, s1.begin()+4, s2.begin()+2, s2.begin()+5);
		}
		// resize
		{
			std::string s1 = "ABC";
			s1.resize(10, '*'); // s1 = "ABC*******"
			s1.resize(2); // s1 = "AB"
			size_t l = s1.length(); // 2
			size_t c = s1.capacity(); // 15
			s1.resize(16); // s1 = "ABC\0\0\0\0\0\0\0\0\0\0\0\0\0"
			c = s1.capacity(); // 30
			s1.shrink_to_fit();
			c = s1.capacity(); // 16
			s1.reserve(33);
			l = s1.length(); // 2
			c = s1.capacity(); // 33
		}
		// substr
		{
			std::string s1 = "ABCDEFGHI";
			std::string s2 = s1.substr(3); // "DEFGHI"
			std::string s3 = s1.substr(3, 6); // "DEFGHI"
			std::string s4;
			if(s1.find("DE") != std::string::npos)
				s4 = s1.substr(s1.find("DE")); // "DEFGHI"
		}
		// find string
		{
			std::string s1 = "ABCDacadabC";
			auto it = s1.rfind('a');
			// bool b = s1.starts_with("AB"); true (C++20)
			// b = s1.ends_with("bC"); true (C++20)
			// b = s1.contains("BC"); true (C++23)
		}
		// example using algo
		{
			auto cond = [](char c){return c == 'a' || c == 'e';};
			auto cond_inv = [](char c){return c != 'a' && c != 'e';};
			std::string s1 = "abecdeafage";
			s1.erase(std::remove_if(begin(s1), end(s1), cond), end(s1)); // s1 = "bcdfg"
			std::cout << s1 << '\n';

			// s1 = "abecdeafage";
			// std::string buff;
			// std::copy_if(s1.begin(), s1.end(), buff.begin(), cond_inv);
			// printf("my buff : %s\n", buff.c_str());

			s1 = "abecdeafage";
			char buff[64];
			std::copy_if(s1.begin(), s1.end(), buff, cond_inv); // s1 = "bcdfg"
		}
	}
	// "std::string Literal"s  C++14
	{
		using namespace std::string_literals;

		auto s1 = R"(raw "C"-string c:\users\joe)";	//char const[]	C++11
		auto s2 = R"(AB\C
		DEF)"s;	//std::string C++ 14
		// Syntax: R"DELIMITER(characters…)DELIMITER"
	}
	// Use std::string_view for read-only parameters!  C++17
	{
		// lightweight  (= cheap to copy, can be passed by value)
		// non-owning  (= not responsible for allocating or deleting memory)
		// read-only view  (= does not allow modification of target string)
		// of a string(-like) object  (std::string / "literal" / …)
		// primary use case: read-only function parameters
		/*
		#include <string>
		#include <string_view>
		int edit_distance (std::string_view s1, std::string_view s2) { … }
		std::string input = "abx";
		int dist = edit_distance("abc", input);
		*/
	}

	// std::getline
	{
		// read entire lines / chunks of text at once
		// target string can be re-used (saving memory)
		/*
		std::string s;
		getline(std::cin, s);        // read entire line
		getline(std::cin, s, '\t');  // read until next tab
		getline(std::cin, s, 'a');   // read until next 'a'
		*/
	}

	return 0;
}
