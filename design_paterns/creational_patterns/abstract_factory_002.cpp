#include <iostream>

using namespace std;

class Shape
{
public:
	virtual void draw() = 0;
};

class Circle : public Shape
{
public:
	Circle(double radius) : radius(radius) {}

	void draw()
	{
		cout << "Drawing Circle with radius " << radius << endl;
	}

private:
	double radius;
};

class CircleFactory
{
public:
	static Circle *create(double radius)
	{
		return new Circle(radius);
	}
};

class Rectangle : public Shape
{
public:
	Rectangle(double width, double height) : width(width), height(height) {}

	void draw()
	{
		cout << "Drawing Rectangle with width " << width << " and height " << height << endl;
	}

private:
	double width, height;
};

class RectangleFactory
{
public:
	static Rectangle *create(double width, double height)
	{
		return new Rectangle(width, height);
	}
};

class Triangle : public Shape
{
public:
	Triangle(double base, double height) : base(base), height(height) {}

	void draw()
	{
		cout << "Drawing Triangle with base " << base << " and height " << height << endl;
	}

private:
	double base, height;
};

class TriangleFactory
{
public:
	static Triangle *create(double base, double height)
	{
		return new Triangle(base, height);
	}
};


int main() {
	Circle* circle = CircleFactory::create(5.0);
	Rectangle* rectangle = RectangleFactory::create(3.0, 4.0);
	Triangle* triangle = TriangleFactory::create(2.0, 5.0);

	circle->draw();     // output: "Drawing Circle with radius 5"
	rectangle->draw();  // output: "Drawing Rectangle with width 3 and height 4"
	triangle->draw();   // output: "Drawing Triangle with base 2 and height 5"

	delete circle;
	delete rectangle;
	delete triangle;
}
