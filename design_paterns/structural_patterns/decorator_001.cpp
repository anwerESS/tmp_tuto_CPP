// The Decorator pattern is a design pattern that allows you to dynamically add functionality to an object at runtime by wrapping it in a decorator object. This pattern is used when you want to add additional features to an object without changing its core functionality or modifying its class.

// The pattern involves creating a core object or component, which can be a class or interface, and then creating one or more decorator classes that wrap the core object and add extra behavior to it. Each decorator class has the same interface as the core object, so they can be used interchangeably.

// The decorators themselves can be stacked or combined to add more functionality to the core object. Each decorator adds its own unique functionality, but the combination of all decorators ultimately determines the full behavior of the object.

// The Decorator pattern allows for more flexibility than traditional subclassing, as it allows you to add functionality to an object at runtime rather than having to create multiple subclasses. It also allows for more granularity in adding functionality, as you can add or remove decorators as needed to create a custom combination of features.

// Overall, the Decorator pattern is useful when you need to add extra functionality to an object without changing its underlying class or when you need to add functionality to an object at runtime. It is commonly used in software applications that require customization or extensibility.

// here are a few examples of the decorator pattern used in real-life scenarios:

// 1. Text formatting: Many text editors, word processors, and web browsers use the decorator pattern to apply different formatting options to text. For example, a basic text object can be decorated with bold, italic, underline, and other formatting options to create a richly formatted document.

// 2. Logging: In software development, logging is the practice of recording application events and messages to help debug and troubleshoot issues. The decorator pattern can be used to add extra logging functionality to an existing class without modifying its core functionality.

// 3. Encryption: Encryption algorithms can be implemented using the decorator pattern to apply different encryption options to a basic plaintext object. For example, a plaintext object can be decorated with AES-256 encryption, SHA-256 hashing, or other security options to create a highly secure data object.

// 4. Audio processing: Audio processing software can use the decorator pattern to add effects and filters to audio streams. For example, a basic audio stream can be decorated with reverb, echo, equalization, and other audio effects to create a customized audio output.

// 5. Graphics rendering: Graphics rendering engines can use the decorator pattern to apply different visual effects to an object or scene. For example, a basic 3D model can be decorated with textures, lighting effects, and other visual enhancements to create a highly realistic rendering.



// In this example, we have a Component interface that defines the basic operations that a concrete component should implement. We have a concrete implementation of this interface called ConcreteComponent. We also have a Decorator class, which implements the same Component interface and holds a reference to another Component. This class can be used to wrap any concrete component and add additional behavior to it. We have two concrete decorators, ConcreteDecoratorA and ConcreteDecoratorB, which both add their own behavior to the component they decorate.

// In the main function, we create a ConcreteComponent object and then wrap it in two decorators, ConcreteDecoratorA and ConcreteDecoratorB. We then call the operation method on the final decorator, which will call the operation methods of all the decorators and the underlying component, resulting in the added behavior of both decorators being called along with the base behavior of the component.

// Note that we're using unique_ptr to manage the ownership of the Component objects, which ensures that the objects will be deleted automatically when they're no longer needed.


#include <iostream>
#include <memory>

using namespace std;

class Component {
public:
	virtual ~Component() {}
	virtual void operation() = 0;
};

class ConcreteComponent : public Component {
public:
	void operation() override {
		cout << "ConcreteComponent operation called." << endl;
	}
};

class Decorator : public Component {
public:
	Decorator(unique_ptr<Component> component) : component_(move(component)) {}

	void operation() override {
		component_->operation();
	}

protected:
	unique_ptr<Component> component_;
};

class ConcreteDecoratorA : public Decorator {
public:
	ConcreteDecoratorA(unique_ptr<Component> component) : Decorator(move(component)) {}

	void operation() override {
		Decorator::operation();
		addedBehavior();
	}

	void addedBehavior() {
		cout << "ConcreteDecoratorA addedBehavior called." << endl;
	}
};

class ConcreteDecoratorB : public Decorator {
public:
	ConcreteDecoratorB(unique_ptr<Component> component) : Decorator(move(component)) {}

	void operation() override {
		Decorator::operation();
		addedBehavior();
	}

	void addedBehavior() {
		cout << "ConcreteDecoratorB addedBehavior called." << endl;
	}
};

int main() {
	unique_ptr<Component> component = make_unique<ConcreteComponent>();
	unique_ptr<Component> decoratorA = make_unique<ConcreteDecoratorA>(move(component));
	unique_ptr<Component> decoratorB = make_unique<ConcreteDecoratorB>(move(decoratorA));

	decoratorB->operation();
	return 0;
}
