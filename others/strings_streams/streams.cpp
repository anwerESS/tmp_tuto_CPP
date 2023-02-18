// https://cplusplus.com/reference/iolibrary/
// https://hackingcpp.com/cpp/std/io_streams.html


///// Elements of the iostream library (char instantitation)
// Classes:
// 		ios_base		Base class for streams (class)
// 		ios	Base 		class for streams (type-dependent components) (class)
// 		istream			Input stream (class)
// 		ostream			Output Stream (class)
// 		iostream		Input/output stream (class)
// 		ifstream		Input file stream class (class)
// 		ofstream		Output file stream (class)
// 		fstream			Input/output file stream class (class)
// 		istringstream	Input string stream (class)
// 		ostringstream	Output string stream (class)
// 		stringstream	Input/output string stream (class)
// 		streambuf		Base buffer class for streams (class)
// 		filebuf			File stream buffer (class)
// 		stringbuf		String stream buffer (class)

// Objects:
// 		cin		Standard input stream (object)
// 		cout	Standard output stream (object)
// 		cerr	Standard output stream for errors (object)
// 		clog	Standard output stream for logging (object)

// Types:
// 		fpos		Stream position class template (class template)
// 		streamoff	Stream offset type (type)
// 		streampos	Stream position type (type)
// 		streamsize	Stream size type (type)

// Manipulators:
// 		boolalpha		Alphanumerical bool values (function)
// 		dec				Use decimal base (function)
// 		endl			Insert newline and flush (function)
// 		ends			Insert null character (function)
// 		fixed			Use fixed floating-point notation (function)
// 		flush			Flush stream buffer (function)
// 		hex	Use 		hexadecimal base (function)
// 		internal		Adjust field by inserting characters at an internal position (function)
// 		left			Adjust output to the left (function)
// 		noboolalpha		No alphanumerical bool values (function)
// 		noshowbase		Do not show numerical base prefixes (function)
// 		noshowpoint		Do not show decimal point (function)
// 		noshowpos		Do not show positive signs (function)
// 		noskipws		Do not skip whitespaces (function)
// 		nounitbuf		Do not force flushes after insertions (function)
// 		nouppercase		Do not generate upper case letters (function)
// 		oct				Use octal base (function)
// 		resetiosflags	Reset format flags (function)
// 		right			Adjust output to the right (function)
// 		scientific		Use scientific floating-point notation (function)
// 		setbase			Set basefield flag (function)
// 		setfill			Set fill character (function)
// 		setiosflags		Set format flags (function)
// 		setprecision	Set decimal precision (function)
// 		setw			Set field width (function)
// 		showbase		Show numerical base prefixes (function)
// 		showpoint		Show decimal point (function)
// 		showpos			Show positive signs (function)
// 		skipws			Skip whitespaces (function)
// 		unitbuf			Flush buffer after insertions (function)
// 		uppercase		Generate upper-case letters (function)
// 		ws				Extract whitespaces (function)

#include <iostream>
#include <iomanip> //  Formatting Manipulators
#include <limits> //  Formatting Manipulators

struct Point {int x; int y;};
std::ostream& operator<<(std::ostream& os, const Point& p);
std::istream& operator >>(std::istream& is, Point& p);


int main(int argc, char const *argv[])
{
	// Custom I/O
	{
		Point p1 {2,3};
		std::cout << p1;
		std::cin >> p1;
	}
	// Skip Forward With ignore
	{
		// std::istream::ignore(n, c)
		// forwards stream by n characters
		// until stop character c
		// skip next 8 characters
		/*
		std::cin.ignore(8);
		// skip by max. 10 characters or until after '='
		std::cin.ignore(10, '=');
		// skip until after next newline character
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		*/
		std::string ss;
		std::cin.ignore(8, 'c') >> ss; // abcdefghijk -> (ss = "defghijk")

	}
	// Formatting Manipulators
	{
		double d = 12.345678;
		double e = 2011;
		double f = 1e-10;

		std::cout << d	// 12.345678
		<< e << '\n'	// 2011
		<< f << '\n'	// 1e-010

		<< std::setprecision(4) 	// # of digits
		<< d << '\n'	// 12.35
		<< e << '\n'	// 2011
		<< f << '\n'	// 1e-010

		<< std::fixed	// fixed # of decimals
		<< d << '\n'	// 12.3457
		<< e << '\n'	// 2011.0000
		<< f << '\n'	// 1.0000e-010

		<< std::scientific	// scientific notation
		<< d << '\n'	// 1.2346e+001
		<< e << '\n'	// 2.0110e+003
		<< f << '\n'	// 1.0000e-010

		<< true <<' '<< false	// 1 0
		<< std::boolalpha	// booleans as string
		<< true <<' '<< false;	// true false


		// modify adjustfield using manipulators
		int n = -77;
		std::cout.width(6); std::cout << std::internal << n << '\n';	// "-   77"
		std::cout.width(6); std::cout << std::left << n << '\n';		// "-77"
		std::cout.width(6); std::cout << std::right << n << '\n';		// "   -77"
	}

	return 0;
}







std::ostream& operator<<(std::ostream& os, const Point& p)
{
	return os << "X : " << p.x << "; Y : " << p.y << "\n";
}

std::istream& operator >>(std::istream& is, Point& p)
{
	return is >> p.x >> p.y;
}

