

#include <iostream>
#include <string>
#include <vector>

// forward declaration
class Car;

// Driver class
class Driver {
public:
	Driver(const std::string& n) : name(n) {}
	const std::string& getName() const { return name; }
private:
	std::string name;
};

// Car class
class Car {
public:
	Car(const std::string& mk, const std::string& md, int y)
		: make(mk), model(md), year(y) {}
	void setDriver(Driver* d) { driver = d; }
	const std::string& getMake() const { return make; }
	const std::string& getModel() const { return model; }
	int getYear() const { return year; }
	Driver* getDriver() const { return driver; }

private:
	std::string make;
	std::string model;
	int year;
	Driver* driver = nullptr;
};

int main() {
	// create drivers
	Driver* john = new Driver("John");
	Driver* mary = new Driver("Mary");

	// create cars and assign drivers
	Car car1("Toyota", "Camry", 2010);
	car1.setDriver(john);

	Car car2("Honda", "Accord", 2015);
	car2.setDriver(mary);

	// list all cars and their drivers
	std::vector<Car> cars{ car1, car2 };
	for (const auto& c : cars) {
		std::cout << "Make: " << c.getMake() << std::endl;
		std::cout << "Model: " << c.getModel() << std::endl;
		std::cout << "Year: " << c.getYear() << std::endl;
		if (c.getDriver()) {
			std::cout << "Driver: " << c.getDriver()->getName() << std::endl;
		}
		else {
			std::cout << "No driver assigned" << std::endl;
		}
	}

	// free memory
	delete john;
	delete mary;
	return 0;
}
