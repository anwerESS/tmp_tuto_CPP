// In this example, we have two classes - Engine and Car. The Car class contains an instance of the Engine class as a private member. This is called composition. The engine belongs exclusively to the car; it cannot exist on its own.

// When we create a Car object, its constructor creates an Engine object alongside it. We can then call startEngine() on the Car object, which calls start() on the contained Engine object, outputting "The engine starts." to the console.

// Composition is often used when one class has ownership over another class, meaning that the lifetime of the contained class is dependent on the lifetime of the containing class. In our example, the engine only exists as long as the car exists.

#include <iostream>
#include <string>
using namespace std;

class Engine {
public:
	void start() {
		cout << "The engine starts." << endl;
	}
};

class Car {
private:
	// Composition: A car "has an" engine
	Engine engine;
public:
	void startEngine() {
		engine.start();
	}
};

int main() {
	Car car;
	car.startEngine();
	return 0;
}
