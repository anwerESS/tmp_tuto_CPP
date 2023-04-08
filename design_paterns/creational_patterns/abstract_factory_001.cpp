// Abstract Factory is a creational design pattern that provides an interface for creating families of related or dependent objects without specifying their concrete classes. It allows you to create objects that are related to each other, but which can vary in type and implementation.

// The Abstract Factory pattern is useful when you need to create a set of related objects that need to work together, but you want to be able to switch between different families of objects without affecting the rest of your code. This pattern provides a way to decouple your code from the specific implementations of the objects you are creating, making it more flexible and easier to maintain.

// The main components of the Abstract Factory pattern are:

// Abstract Factory: an interface that defines the operations for creating abstract product objects.
// Concrete Factory: a concrete implementation of the abstract factory interface that creates concrete product objects.
// Abstract Product: an interface that defines the operations for a family of related products.
// Concrete Product: a concrete implementation of the abstract product interface.
// Here's an example of how the Abstract Factory pattern could be used in a GUI application:

// Suppose you are building a GUI application that needs to support multiple operating systems, such as Windows and macOS. You want your application to have a consistent look and feel across all platforms, but the underlying implementation of the GUI components will be different on each platform. In this case, you could use the Abstract Factory pattern to create a set of related objects for each platform:

// GUIFactory interface: defines the operations for creating abstract GUI components.
// WindowsGUIFactory and MacOSGUIFactory classes: concrete implementations of the GUIFactory interface that create concrete GUI components for Windows and macOS, respectively.
// Button, Label, and TextField interfaces: define the operations for a family of related GUI components.
// WindowsButton, WindowsLabel, WindowsTextField, MacOSButton, MacOSLabel, and MacOSTextField classes: concrete implementations of the Button, Label, and TextField interfaces for Windows and macOS, respectively.
// With this implementation, you can create a factory object based on the current operating system, which will create the appropriate set of GUI components for that platform. This allows your application to work seamlessly on multiple operating systems, without having to worry about the underlying implementation of the GUI components.



// The Abstract Factory pattern is used in many real-life scenarios where a system needs to support multiple families of related or dependent objects. Here are some examples:

// GUI toolkit: A GUI toolkit, such as Java Swing or .NET Windows Forms, uses the Abstract Factory pattern to provide a set of related GUI components that can be customized to work with different platforms or themes.

// Database drivers: A database driver that needs to support multiple database management systems (DBMS), such as Oracle, MySQL, and PostgreSQL, can use the Abstract Factory pattern to provide a set of related objects for each DBMS.

// Vehicle manufacturing: A vehicle manufacturing company can use the Abstract Factory pattern to create families of related components, such as engines, chassis, and tires, that can be customized for different types of vehicles, such as cars, trucks, and motorcycles.

// Game development: A game development company can use the Abstract Factory pattern to create families of related objects for different types of games, such as character classes, weapons, and power-ups.

// Operating systems: Operating systems, such as Windows, macOS, and Linux, use the Abstract Factory pattern to provide a set of related system components that can be customized for different hardware architectures or system configurations.

// Mobile application development: A mobile application development company can use the Abstract Factory pattern to create families of related objects for different mobile platforms, such as iOS and Android, or for different device types, such as smartphones and tablets.

// In each of these scenarios, the Abstract Factory pattern provides a way to create families of related or dependent objects without tightly coupling the code to specific implementations. This makes the system more flexible and easier to maintain, especially when new families of objects need to be added or existing ones need to be modified.

// /////////////////////////////////////////////////////////
// In this example, we have an abstract factory GUIFactory with two abstract products: Window and Button. We have two concrete factories, WindowsGUIFactory and MacOSGUIFactory, each of which creates concrete implementations of the abstract products for their respective platforms.

// We then create instances of the factories for Windows and macOS, and use them to create windows and buttons for each platform. Finally, we call the draw and click methods on the windows and buttons, respectively.

// This implementation demonstrates how the Abstract Factory pattern allows us to create families of related objects that can be customized for different platforms or use cases.

/*
+-----------------------+             +-----------------------+
|      AbstractFactory   |             |        AbstractProduct |
+-----------------------+             +-----------------------+
| + createProductA()     |             |                       |
| + createProductB()     |<----------+ |      <<interface>>    |
+-----------------------+             |       AbstractProductA |
									   |                       |
									   +-----------------------+
									   | + operation()          |
									   +-----------------------+
													  /_\
													   |
													   |
													   |
													   |
+-----------------------+             +-----------------------+
|    ConcreteFactory1   |             |     ConcreteProductA1  |
+-----------------------+             +-----------------------+
| + createProductA()     |<----------+ |                       |
| + createProductB()     |             |                       |
+-----------------------+             +-----------------------+
													   /_\
														|
														|
														|
														|
+-----------------------+             +-----------------------+
|    ConcreteFactory2   |             |     ConcreteProductA2  |
+-----------------------+             +-----------------------+
| + createProductA()     |<----------+ |                       |
| + createProductB()     |             |                       |
+-----------------------+             +-----------------------+

*/

#include <iostream>
#include <memory>

// Abstract Product A
class Window {
public:
	virtual void draw() = 0;
};

// Concrete Product A1
class WindowsWindow : public Window {
public:
	void draw() override {
		std::cout << "Windows Window drawn." << std::endl;
	}
};

// Concrete Product A2
class MacOSWindow : public Window {
public:
	void draw() override {
		std::cout << "macOS Window drawn." << std::endl;
	}
};

// Abstract Product B
class Button {
public:
	virtual void click() = 0;
};

// Concrete Product B1
class WindowsButton : public Button {
public:
	void click() override {
		std::cout << "Windows Button clicked." << std::endl;
	}
};

// Concrete Product B2
class MacOSButton : public Button {
public:
	void click() override {
		std::cout << "macOS Button clicked." << std::endl;
	}
};

// Abstract Factory
class GUIFactory {
public:
	virtual std::unique_ptr<Window> createWindow() = 0;
	virtual std::unique_ptr<Button> createButton() = 0;
};

// Concrete Factory for Windows
class WindowsGUIFactory : public GUIFactory {
public:
	std::unique_ptr<Window> createWindow() override {
		return std::make_unique<WindowsWindow>();
	}
	std::unique_ptr<Button> createButton() override {
		return std::make_unique<WindowsButton>();
	}
};

// Concrete Factory for macOS
class MacOSGUIFactory : public GUIFactory {
public:
	std::unique_ptr<Window> createWindow() override {
		return std::make_unique<MacOSWindow>();
	}
	std::unique_ptr<Button> createButton() override {
		return std::make_unique<MacOSButton>();
	}
};

int main() {
	std::unique_ptr<GUIFactory> factory;

	// Create factory for Windows
	factory = std::make_unique<WindowsGUIFactory>();
	auto win = factory->createWindow();
	auto btn = factory->createButton();
	win->draw();
	btn->click();

	// Create factory for macOS
	factory = std::make_unique<MacOSGUIFactory>();
	win = factory->createWindow();
	btn = factory->createButton();
	win->draw();
	btn->click();

	///////////// output ////////////
	// Windows Window drawn.
	// Windows Button clicked.
	// macOS Window drawn.
	// macOS Button clicked.
	/////////////////////////////////
	return 0;
}
