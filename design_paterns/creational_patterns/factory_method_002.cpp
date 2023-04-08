// In this example, we have an abstract Vehicle interface that defines the signature of the getName() and getMaxSpeed() methods. We also have three concrete vehicle classes, Car, Motorcycle, and Truck, which implement these methods to return the names and maximum speeds of the respective vehicles.

// Next, we have an abstract VehicleFactory interface that defines the signature of the createVehicle() method. We also have three concrete factory classes, CarFactory, MotorcycleFactory, and TruckFactory, which implement the createVehicle() method to create instances of the respective vehicle classes.

// In the client code, we create a vector of VehicleFactory objects (CarFactory, MotorcycleFactory, and TruckFactory). We then iterate over the vector, using each factory to create a Vehicle object, print out the vehicle type and maximum speed using the getName() and getMaxSpeed() methods, and delete the objects to prevent memory leaks.

// This example demonstrates how the Factory Method pattern can be used to create multiple types of objects (in this case, different types of vehicles) using a common interface (in this case, the VehicleFactory interface).


#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Abstract product interface
class Vehicle {
public:
	virtual ~Vehicle() {}
	virtual string getName() const = 0;
	virtual int getMaxSpeed() const = 0;
};

// Concrete product classes
class Car : public Vehicle {
public:
	string getName() const override {
		return "Car";
	}

	int getMaxSpeed() const override {
		return 200; // km/h
	}
};

class Motorcycle : public Vehicle {
public:
	string getName() const override {
		return "Motorcycle";
	}

	int getMaxSpeed() const override {
		return 300; // km/h
	}
};

class Truck : public Vehicle {
public:
	string getName() const override {
		return "Truck";
	}

	int getMaxSpeed() const override {
		return 100; // km/h
	}
};

// Abstract factory interface
class VehicleFactory {
public:
	virtual ~VehicleFactory() {}
	virtual Vehicle* createVehicle() const = 0;
};

// Concrete factory classes
class CarFactory : public VehicleFactory {
public:
	Vehicle* createVehicle() const override {
		return new Car();
	}
};

class MotorcycleFactory : public VehicleFactory {
public:
	Vehicle* createVehicle() const override {
		return new Motorcycle();
	}
};

class TruckFactory : public VehicleFactory {
public:
	Vehicle* createVehicle() const override {
		return new Truck();
	}
};

// Client code
int main() {
	vector<VehicleFactory*> factories = { new CarFactory(), new MotorcycleFactory(), new TruckFactory() };
	for (VehicleFactory* factory : factories) {
		Vehicle* vehicle = factory->createVehicle();
		cout << "Vehicle type: " << vehicle->getName() << endl;
		cout << "Max speed: " << vehicle->getMaxSpeed() << " km/h" << endl;
		delete vehicle;
	}

	/////////////// output ////////////
	// Vehicle type: Car
	// Max speed: 200 km/h
	// Vehicle type: Motorcycle
	// Max speed: 300 km/h
	// Vehicle type: Truck
	// Max speed: 100 km/h
	///////////////////////////////////

	for (VehicleFactory* factory : factories) {
		delete factory;
	}

	return 0;
}
