
// Visitor is a behavioral design pattern that allows adding new behaviors to existing class hierarchy without altering any existing code.

// here are some real-life examples where the Visitor pattern could be useful:

// GUI components: In a GUI application, the Visitor pattern can be used to traverse the component hierarchy and perform operations on each component, such as drawing or updating its state. For example, a Window class could be an Element that accepts a Visitor object to update its state or render its contents, and different Visitor objects could be created to implement different operations, such as printing or saving the contents of the window.

// Compiler design: In a compiler, the Visitor pattern can be used to traverse the abstract syntax tree (AST) and perform operations on each node. For example, a Statement or Expression class could be an Element that accepts a Visitor object to perform type checking, code generation, or other transformations on the node. Different Visitor objects could be created to implement different stages of the compilation process, such as parsing, analysis, and optimization.

// Financial analysis: In a financial application, the Visitor pattern can be used to analyze financial data and perform calculations on each data point. For example, a FinancialData class could be an Element that accepts a Visitor object to calculate statistics such as mean, median, and standard deviation. Different Visitor objects could be created to implement different financial models, such as pricing options or forecasting future trends.

// Game development: In a game engine, the Visitor pattern can be used to update the game state and render the game world. For example, a GameObject class could be an Element that accepts a Visitor object to perform physics calculations or render the object on the screen. Different Visitor objects could be created to implement different game modes, such as single player or multiplayer, or to implement special effects such as particle systems or lighting.

/**
 * The Visitor Interface declares a set of visiting methods that correspond to
 * component classes. The signature of a visiting method allows the visitor to
 * identify the exact class of the component that it's dealing with.
 */

#include <iostream>
#include <array>

class ConcreteComponentA;
class ConcreteComponentB;

class Visitor
{
public:
	virtual void VisitConcreteComponentA(const ConcreteComponentA *element) const = 0;
	virtual void VisitConcreteComponentB(const ConcreteComponentB *element) const = 0;
};

/**
 * The Component interface declares an `accept` method that should take the base
 * visitor interface as an argument.
 */

class Component
{
public:
	virtual ~Component() {}
	virtual void Accept(Visitor *visitor) const = 0;
};

/**
 * Each Concrete Component must implement the `Accept` method in such a way that
 * it calls the visitor's method corresponding to the component's class.
 */
class ConcreteComponentA : public Component
{
	/**
	 * Note that we're calling `visitConcreteComponentA`, which matches the
	 * current class name. This way we let the visitor know the class of the
	 * component it works with.
	 */
public:
	void Accept(Visitor *visitor) const override
	{
		visitor->VisitConcreteComponentA(this);
	}
	/**
	 * Concrete Components may have special methods that don't exist in their base
	 * class or interface. The Visitor is still able to use these methods since
	 * it's aware of the component's concrete class.
	 */
	std::string ExclusiveMethodOfConcreteComponentA() const
	{
		return "A";
	}
};

class ConcreteComponentB : public Component
{
	/**
	 * Same here: visitConcreteComponentB => ConcreteComponentB
	 */
public:
	void Accept(Visitor *visitor) const override
	{
		visitor->VisitConcreteComponentB(this);
	}
	std::string SpecialMethodOfConcreteComponentB() const
	{
		return "B";
	}
};

/**
 * Concrete Visitors implement several versions of the same algorithm, which can
 * work with all concrete component classes.
 *
 * You can experience the biggest benefit of the Visitor pattern when using it
 * with a complex object structure, such as a Composite tree. In this case, it
 * might be helpful to store some intermediate state of the algorithm while
 * executing visitor's methods over various objects of the structure.
 */
class ConcreteVisitor1 : public Visitor
{
public:
	void VisitConcreteComponentA(const ConcreteComponentA *element) const override
	{
		std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor1\n";
	}

	void VisitConcreteComponentB(const ConcreteComponentB *element) const override
	{
		std::cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor1\n";
	}
};

class ConcreteVisitor2 : public Visitor
{
public:
	void VisitConcreteComponentA(const ConcreteComponentA *element) const override
	{
		std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor2\n";
	}
	void VisitConcreteComponentB(const ConcreteComponentB *element) const override
	{
		std::cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor2\n";
	}
};
/**
 * The client code can run visitor operations over any set of elements without
 * figuring out their concrete classes. The accept operation directs a call to
 * the appropriate operation in the visitor object.
 */
void ClientCode(std::array<const Component *, 2> components, Visitor *visitor)
{
	// ...
	for (const Component *comp : components)
	{
		comp->Accept(visitor);
	}
	// ...
}

int main()
{
	std::array<const Component *, 2> components = {new ConcreteComponentA, new ConcreteComponentB};
	std::cout << "The client code works with all visitors via the base Visitor interface:\n";
	ConcreteVisitor1 *visitor1 = new ConcreteVisitor1;
	ClientCode(components, visitor1);
	std::cout << "\n";
	std::cout << "It allows the same client code to work with different types of visitors:\n";
	ConcreteVisitor2 *visitor2 = new ConcreteVisitor2;
	ClientCode(components, visitor2);

	////////////// output ///////////
	// 	The client code works with all visitors via the base Visitor interface:
	// A + ConcreteVisitor1
	// B + ConcreteVisitor1

	// It allows the same client code to work with different types of visitors:
	// A + ConcreteVisitor2
	// B + ConcreteVisitor2
	/////////////////////////////////

	for (const Component *comp : components)
	{
		delete comp;
	}
	delete visitor1;
	delete visitor2;

	return 0;
}