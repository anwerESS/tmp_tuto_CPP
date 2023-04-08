// in C++, the pointer to implementation (PIMPL) is a programming technique that enables developers to hide the implementation details of a class from its users. PIMPL is also known as the "Opaque Pointer" design pattern.

// The PIMPL technique is based on the idea of separating the interface of a class from its implementation. Instead of defining all the data members and member functions of a class in its header file, the header file only contains a declaration of the class and a pointer to its implementation. The actual implementation of the class is defined in a separate source file, which is not visible to the users of the class.

// By using PIMPL, developers can change the implementation of a class without affecting the interface or the users of the class. This provides greater flexibility and modularity in the codebase.



// In this example, the Widget class only declares a pointer to its implementation (Impl* pImpl), which is defined in the Widget.cpp source file. This allows the Impl class to be changed or modified without affecting the users of the Widget class.

// Using PIMPL can increase compilation times and introduce additional memory overhead, so it should only be used when necessary, such as in cases where the implementation details of a class need to be hidden from its users.

#include <iostream>

// Widget.h
class Widget {
public:
	Widget();
	~Widget();
	void doSomething();
private:
	class Impl;
	Impl* pImpl;
};

// Widget.cpp
class Widget::Impl {
public:
	void doSomething();
private:
	int mData;
};

Widget::Widget() : pImpl(new Impl) {}
Widget::~Widget() { delete pImpl; }
void Widget::doSomething() { pImpl->doSomething(); }
void Widget::Impl::doSomething() { std::cout << "DATA : "<< mData << "\n";}

int main(int argc, char const *argv[])
{
	Widget myWidget;
	myWidget.doSomething();

	return 0;
}
