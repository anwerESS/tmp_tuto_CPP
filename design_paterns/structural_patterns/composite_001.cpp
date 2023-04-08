// The Composite Design Pattern is a structural pattern in software design that allows you to compose objects into tree structures and then work with these structures as if they were individual objects. It lets you treat individual objects and groups of objects in a uniform manner, making your code more flexible and extensible.

// The key idea behind the Composite Design Pattern is that you can create a class hierarchy where some classes represent individual objects, while others represent groups of objects. Both individual objects and groups of objects can be treated in a uniform manner using a common interface or abstract class. This allows clients of the code to work with the objects and groups of objects in a transparent manner.

// The Composite Design Pattern is useful in a wide range of situations where you need to manipulate complex object hierarchies. Some common examples of where you might use the Composite pattern include graphical user interfaces, file systems, and organizational charts.

// To implement the Composite pattern, you typically define an abstract base class or interface that defines the common operations that can be performed on both individual objects and groups of objects. You then create concrete classes that implement this interface, representing individual objects and groups of objects. The composite class itself holds a collection of these objects, and implements the common interface by delegating operations to the objects it contains.

// Overall, the Composite Design Pattern is a powerful tool for managing complex object hierarchies in a flexible and extensible way. By allowing you to treat individual objects and groups of objects in a uniform manner, it can simplify your code and make it easier to maintain over time.

// The Composite Design Pattern can be used in a variety of real-life scenarios where objects have a tree-like structure and the same operations need to be performed on both individual and composite objects. Here are a few examples:

// 1. GUI Widgets: Graphical user interface (GUI) widgets such as buttons, text boxes, and drop-down lists can be represented as composite objects made up of individual objects such as labels and input fields. The Composite Design Pattern can be used to manage the hierarchy of the widgets and apply the same operations to both individual widgets and composite widgets.

// 2. File Systems: A file system can be thought of as a tree-like structure, with individual files and directories as the leaf nodes, and composite directories as the internal nodes. The Composite Design Pattern can be used to manage the hierarchy of files and directories and perform operations such as copying, moving, and deleting on both individual files and composite directories.

// 3. Graphics Rendering: Graphics rendering software often needs to render complex scenes made up of individual objects such as shapes, lines, and curves, as well as composite objects such as groups of shapes. The Composite Design Pattern can be used to manage the hierarchy of objects in the scene and apply the same rendering operations to both individual objects and composite objects.

// 4. Organization Charts: An organization chart can be represented as a tree-like structure, with individual employees as leaf nodes, and composite nodes such as departments and teams as internal nodes. The Composite Design Pattern can be used to manage the hierarchy of employees and departments, and apply the same operations such as promotions and demotions to both individual employees and composite departments.

// 5. Medical Records: Medical records can be organized as a tree-like structure, with individual medical tests and diagnoses as leaf nodes, and composite nodes such as patient visits and medical conditions as internal nodes. The Composite Design Pattern can be used to manage the hierarchy of medical records and apply the same operations such as searching and filtering to both individual medical tests and composite medical conditions.
/////////////////////////////////////////////////////////////////////////
// In this example, we have a base Component class with two subclasses, Leaf and Composite. Leaf represents individual objects, while Composite represents groups of objects.

// The Composite class contains a collection of Component objects, which it can treat as a single object using the common Component interface. It also provides methods for adding and removing components from the collection.

// In the main() function, we create a hierarchy of Leaf and Composite objects, and call the operation() method on the top-level Composite object. This results in a recursive traversal of the object hierarchy, with each Component object executing its own implementation of the operation() method.
/*
				 +-----------------+
				 |    Component    |
				 +-----------------+
				 |   operation()   |
				 +-----------------+
						/      \
					   /        \
					  /          \
		 +------------+        +------------+
		 |    Leaf    |        |  Composite |
		 +------------+        +------------+
		 | operation()|        | operation()|
		 +------------+        +------------+
							   |  add()     |
							   |  remove()  |
							   +------------+
*/


#include <iostream>
#include <vector>
#include <algorithm>

class Component {
public:
	virtual ~Component() = default;
	virtual void operation() = 0;
};

class Leaf : public Component {
public:
	void operation() override {
		std::cout << "Leaf operation" << std::endl;
	}
};

class Composite : public Component {
public:
	void operation() override {
		std::cout << "Composite operation" << std::endl;
		for (auto& component : components) {
			component->operation();
		}
	}

	void add(Component* component) {
		components.push_back(component);
	}

	void remove(Component* component) {
		auto it = std::find(components.begin(), components.end(), component);
		if (it != components.end()) {
			components.erase(it);
		}
	}

private:
	std::vector<Component*> components;
};

int main() {
	Leaf leaf1;
	Leaf leaf2;
	Leaf leaf3;

	Composite composite1;
	composite1.add(&leaf1);
	composite1.add(&leaf2);

	Composite composite2;
	composite2.add(&composite1);
	composite2.add(&leaf3);

	composite2.operation();

	///////////// output ////////////
	// Composite operation
	// Composite operation
	// Leaf operation
	// Leaf operation
	// Leaf operation
	/////////////////////////////////

	return 0;
}

