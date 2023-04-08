// The Builder design pattern is a creational pattern that allows you to create complex objects step-by-step, by separating the construction of the object from its representation. The pattern involves separating the construction of a complex object from its representation, so that the same construction process can create different representations.

// The Builder pattern is useful when you need to create complex objects that have many components or parts. By using the Builder pattern, you can simplify the process of creating these objects by breaking them down into smaller, more manageable pieces.

// In the Builder pattern, you have a builder object that is responsible for building the object, and a director object that controls the builder object. The builder object knows how to create each part of the object, while the director object knows the order in which to create the parts.

// The builder object has methods for setting the various properties of the object being built, and a method for returning the final product. By using these methods, you can create an object step-by-step, without having to worry about the order in which the steps are performed.

// Overall, the Builder pattern is a useful technique for creating complex objects that have many components or parts, and it can help you simplify the process of creating these objects by breaking them down into smaller, more manageable pieces.


// Here are some examples of how the Builder design pattern can be used in real life:

// User Interface Design: The Builder pattern can be used to construct complex user interface components, such as forms or dialog boxes. The builder object can create each individual element of the interface, such as buttons or text boxes, and the director object can arrange them in the correct layout.

// Document Creation: The Builder pattern can be used to create complex documents, such as PDF files or web pages. The builder object can create each individual component of the document, such as text or images, and the director object can arrange them in the correct order.

// Manufacturing: The Builder pattern can be used in manufacturing to create complex products that have many components. For example, a car manufacturer could use the Builder pattern to create cars with different options, such as different engines or interior features.

// Restaurant Orders: The Builder pattern can be used in restaurants to create complex orders that have many components. For example, a customer could order a pizza with different toppings, sauces, and crusts. The builder object could create each individual component of the pizza, and the director object could assemble them in the correct order.

// Overall, the Builder pattern is useful in situations where you need to create complex objects with many components, and where you want to simplify the process of creating these objects by breaking them down into smaller, more manageable pieces.

///////////////////////////////////
// This code demonstrates how the Builder pattern can be used to create a complex object (the Product class) step-by-step using a Director object that controls a ConcreteBuilder object. The ConcreteBuilder object is responsible for constructing each part of the Product, while the Director object specifies the order in which the parts are constructed. Finally, the Product object is returned by the ConcreteBuilder and its contents are displayed.


/*
		 +-----------------+
		 |    Director     |
		 +-----------------+
		 |                 |
		 +-----------------+
				  |
				  |controls
				  |
		 +-----------------+
		 |     Builder     |
		 +-----------------+
		 | + buildPartA()  |
		 | + buildPartB()  |
		 | + buildPartC()  |
		 | + getResult()   |
		 +-----------------+
				  ^
				  |implements
				  |
		 +-----------------+
		 | ConcreteBuilder |
		 +-----------------+
		 | + buildPartA()  |
		 | + buildPartB()  |
		 | + buildPartC()  |
		 | + getResult()   |
		 +-----------------+
				  ^
				  |creates
				  |
		 +-----------------+
		 |     Product     |
		 +-----------------+
		 | + setPartA()    |
		 | + setPartB()    |
		 | + setPartC()    |
		 | + showProduct() |
		 +-----------------+
*/




#include <iostream>
#include <string>
using namespace std;

class Product {
public:
	void setPartA(const string& partA) {
		m_partA = partA;
	}

	void setPartB(const string& partB) {
		m_partB = partB;
	}

	void setPartC(const string& partC) {
		m_partC = partC;
	}

	void showProduct() const {
		cout << "Part A: " << m_partA << endl;
		cout << "Part B: " << m_partB << endl;
		cout << "Part C: " << m_partC << endl;
	}

private:
	string m_partA;
	string m_partB;
	string m_partC;
};

class Builder {
public:
	virtual void buildPartA() = 0;
	virtual void buildPartB() = 0;
	virtual void buildPartC() = 0;
	virtual Product getResult() = 0;
};

class ConcreteBuilder : public Builder {
public:
	ConcreteBuilder() {
		m_product = new Product();
	}

	void buildPartA() {
		m_product->setPartA("Part A built by ConcreteBuilder");
	}

	void buildPartB() {
		m_product->setPartB("Part B built by ConcreteBuilder");
	}

	void buildPartC() {
		m_product->setPartC("Part C built by ConcreteBuilder");
	}

	Product getResult() {
		return *m_product;
	}

private:
	Product* m_product;
};

class Director {
public:
	Director(Builder* builder) {
		m_builder = builder;
	}

	void construct() {
		m_builder->buildPartA();
		m_builder->buildPartB();
		m_builder->buildPartC();
	}

private:
	Builder* m_builder;
};

int main() {
	ConcreteBuilder builder;
	Director director(&builder);
	director.construct();
	Product product = builder.getResult();
	product.showProduct();

	/////////// output ////////
	// Part A: Part A built by ConcreteBuilder
	// Part B: Part B built by ConcreteBuilder
	// Part C: Part C built by ConcreteBuilder
	//////////////////////////


	return 0;
}
