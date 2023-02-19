


#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

class PolarPosition {public: double R, Ang; PolarPosition(double R, double Ang):R(R),Ang(Ang){}};


class Point {
public:
	int x,y;
	Point(int x = 0, int y = 0):x(x),y(y){}
	void printPoint(){cout << "P(" << x << ',' << y << ")\n";}

	// Binary operator =>	 +, -, *, /, %
	Point operator +(const Point& p){return Point(p.x + this->x, p.y + this->y);}
	Point operator +(int val){return Point(this->x + val, this->y + val);}


	// Unary operator =>	+, -, ++, —
	Point operator-(){return Point(-x,-y);}
	Point operator++(){return Point(++x,++y);} // prefix ++
	Point operator++(int){return Point(x++,y++);} // postfix ++


	// Subscript Array =>	[ ]
	int& operator[](int idx) {
		if(idx < 0 || idx > 1) throw out_of_range("idx must be 0 or 1");
		return (idx == 0)? x : y;
	}

	// Assignment =>	=, +=,*=, /=,-=, %=
	void operator+=(int i){x+=i; y+=i;}

	// Relational =>	>, < , = =, <=, >=
	bool operator>(const Point& p){ return ((x*x + y*y)) >(p.x*p.x + p.y*p.y); }

	// Stream Operator
	friend ostream& operator<< (ostream& os, const Point& p){ return os << "P(" << p.x << ',' << p.y << ')';}
	friend istream& operator>> (istream& is, Point& p){cout<<"insert X and Y\n"; return is >> p.x >> p.y;}

	/// Type cast operator
	operator const char * (){stringstream ss; ss << '(' << x << ',' << y << ')'; return ss.str().c_str();}
	operator PolarPosition(){return PolarPosition{sqrt(x*x+y*y), atan2(y, x)};}


	// Bit- wise =>		& , | , << , >> , ~ , ^
	// Function call =>	()
	// Logical =>	& &,  | |, !


};


int main(int argc, char const *argv[])
{


	Point p1(3, 4);
	Point p2(4, 1);
	//---------------- /// Type cast operator
	{
		PolarPosition polPos = p1;
		printf("R = %f;   ANG = %f\n", polPos.R, polPos.Ang);

		const char *  au = p1;
		printf("AU : %s\n", au);
	}
	//---------------- /// Binary operator
	{
		Point p3 = p1 + p2;
		printf("P3 : (%d, %d)\n", p3.x, p3.y);
	}
	{
		Point p3 = p1 + 10;
		cout << p3 << '\n'; // P(13,14)
	}
	//---------------- /// Unary operator
	{
		Point p3 = -p1;
		const char * p3_s = p3;
		printf("P : %s\n", p3_s); // P : (-3,-4)
	}
	{
		++p1;
		cout << p1 << '\n';
	}
	{
		p1++;
		cout << p1 << '\n';
	}
	//---------------- /// Subscript Array
	{
		p1[0] = 11; p1[1] = 22;
		cout << "X : " << p1[0] << '\n';
		cout << "Y : " << p1[1] << '\n';

		try{p1[3] = 33;} catch(const exception& e){cout << e.what() << '\n';}
	}
	//---------------- /// Stream Operator
	{
		Point p3;
		cin >> p3;
		cout << p3 << '\n';
	}
	//---------------- /// // Assignment
	{
		p1 += 100;
		cout << p1 << '\n';
	}
	//---------------- /// Relational
	{
		cout << (p1 > p2) << '\n';	// 1
	}
	//----------------


	return 0;
}
