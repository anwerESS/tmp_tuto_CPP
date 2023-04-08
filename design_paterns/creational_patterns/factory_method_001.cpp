// The Factory Method pattern is a popular design pattern in object-oriented programming that provides an interface for creating objects in a superclass but allows subclasses to alter the type of objects that will be created.

// The Factory Method pattern is useful when you need to create an object, but you don't know what type of object it will be until runtime. Rather than hardcoding the object creation code in a single class, the Factory Method pattern allows you to define an interface for creating objects and delegate the responsibility for object instantiation to subclasses.

// Here's how the Factory Method pattern works:

// First, you define an interface or an abstract class that specifies the signature of the factory method. This method will be responsible for creating objects.

// Next, you create one or more concrete classes that implement the interface or abstract class defined in step 1. Each of these classes represents a different type of object that can be created.

// When you need to create an object, you call the factory method defined in step 1. The specific implementation of the factory method is determined by the subclass that is instantiated.

// The factory method creates and returns an object of the appropriate type.

// One of the main advantages of using the Factory Method pattern is that it promotes loose coupling between classes. The code that creates objects is isolated from the code that uses those objects, which makes it easier to modify or extend the application in the future.

// Another benefit of the Factory Method pattern is that it can be used to implement the Dependency Inversion Principle. This principle states that high-level modules should not depend on low-level modules, but both should depend on abstractions. By using the Factory Method pattern, you can ensure that your code depends on abstractions rather than concrete implementations.

// The Factory Method pattern can be used in many real-life scenarios where object creation needs to be abstracted away from the client code that uses those objects. Here are a few examples:

// 1. Database connections: In a database application, different types of database connections may be required depending on the database being used. The Factory Method pattern can be used to create a database connection object based on the type of database being used.

// GUI 2. frameworks: GUI frameworks often use the Factory Method pattern to create different types of widgets, such as buttons, text boxes, and drop-down lists. The factory method can be used to encapsulate the creation of these widgets and make it easier to add new types of widgets in the future.

// 3. E-commerce websites: In an e-commerce website, different products may have different shipping requirements. The Factory Method pattern can be used to create shipping objects for each product type, such as standard shipping, expedited shipping, or overnight shipping.

// 4. Video games: Video game engines often use the Factory Method pattern to create different types of game objects, such as characters, enemies, weapons, and power-ups. The factory method can be used to abstract away the creation of these objects and make it easier to add new types of game objects in the future.

// 5. Logging frameworks: In a logging framework, different types of loggers may be required for different purposes, such as file logging, database logging, or console logging. The Factory Method pattern can be used to create logger objects for each type of logging, and make it easier to add new types of logging in the future.

// 6. Document processing applications: Document processing applications often use the Factory Method pattern to create different types of document objects, such as text documents, spreadsheets, and presentations. The factory method can be used to abstract away the creation of these objects and make it easier to add new types of documents in the future.

// These are just a few examples of how the Factory Method pattern can be used in real-life scenarios. In general, the Factory Method pattern is useful in any situation where you need to abstract away the creation of objects and make it easier to add new types of objects in the future.

///////////////////////////////////////////////////////

// In this code, we have an abstract Product interface that defines the signature of the getName() method. We also have two concrete product classes, ProductA and ProductB, which implement the getName() method in their own way.

// Next, we have an abstract Factory interface that defines the signature of the createProduct() method. We also have two concrete factory classes, FactoryA and FactoryB, which implement the createProduct() method to create either ProductA or ProductB objects.

// Finally, in the client code, we create a concrete factory object (FactoryA in this case), and use it to create a product object (ProductA in this case). We then print out the name of the product using the getName() method, and delete the objects to prevent memory leaks.

// Note that by replacing FactoryA with FactoryB in the client code, we can create a different type of product object (ProductB in this case). This demonstrates the flexibility of the Factory Method pattern.

/*
				+------------------+
				|     Product      |
				+------------------+
				| <<interface>>    |
				|  getName() const |
				+------------------+
						 ^
						 |
		  +--------------+---------------+
		  |                              |
+----------------+               +----------------+
|   ProductA     |               |   ProductB     |
+----------------+               +----------------+
| getName() const|               | getName() const|
+----------------+               +----------------+



			   +----------------+
			   |    Factory     |
			   +----------------+
			   | <<interface>>  |
			   |createProduct() |
			   +----------------+
						 ^
						 |
		  +--------------+---------------+
		  |                              |
	 +---------+                  +---------+
	 |FactoryA |                  |FactoryB |
	 +---------+                  +---------+
	 |createProduct()|             |createProduct()|
	 +----------------+           +----------------+

*/

#include <iostream>
#include <string>
using namespace std;

// Abstract product interface
class Product {
public:
	virtual ~Product() {}
	virtual string getName() const = 0;
};

// Concrete product A
class ProductA : public Product {
public:
	string getName() const override {
		return "Product A";
	}
};

// Concrete product B
class ProductB : public Product {
public:
	string getName() const override {
		return "Product B";
	}
};

// Abstract factory interface
class Factory {
public:
	virtual ~Factory() {}
	virtual Product* createProduct() const = 0;
};

// Concrete factory A
class FactoryA : public Factory {
public:
	Product* createProduct() const override {
		return new ProductA();
	}
};

// Concrete factory B
class FactoryB : public Factory {
public:
	Product* createProduct() const override {
		return new ProductB();
	}
};

// Client code
int main() {
	Factory* factory = new FactoryA(); // Can be replaced with FactoryB
	Product* product = factory->createProduct();
	cout << "Product name: " << product->getName() << endl;

	//////////// output ///////////
	// Product name: Product A
	//////////////////////////////

	delete product;
	delete factory;
	return 0;
}
