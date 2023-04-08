
// In this example, the Engine and Body classes represent the components of a car, while the Car class represents the final product. The CarBuilder class implements the Builder interface to construct each component. The Director class controls the construction process by directing the CarBuilder on which components to build and in which order. Finally, in the main function, the Director is used to build a Car object, which is then displayed using the showCar() method.

// The Engine and Body classes have setter methods to set their various attributes, such as horsepower and color. They also have show methods to display the current values of their attributes. The Car class has setter methods for the Engine and Body objects, as well as a showCar method that calls the show methods of its Engine and Body objects.

// The Builder interface has three pure virtual methods: buildEngine, buildBody, and getResult. buildEngine and buildBody are used to construct the Engine and Body objects, respectively. getResult returns the final Car object.

// The CarBuilder class implements the Builder interface. It has two private member variables, m_engine and m_body, which represent the Engine and Body objects being constructed. In its buildEngine and buildBody methods, it sets the attributes of the m_engine and m_body objects, respectively. Finally, in its getResult method, it constructs a new Car object using its m_engine and m_body member variables and returns it.

// The Director class has a private member variable, a pointer to a Builder object. Its constructor takes a pointer to a Builder object and sets its m_builder member variable to that object. Its construct method calls the buildEngine and buildBody methods of its m_builder object in the appropriate order.

// In the main function, a CarBuilder object is created, and a Director object is created with a pointer to the CarBuilder. The construct method of the Director is called to build the Car. Finally, the getResult method of the CarBuilder is called to obtain the final Car object, which is then displayed using the showCar method.



/*
+------------------+          +-----------------+           +------------+
|     Director     |          |     Builder     |           |     Car    |
+------------------+          +-----------------+           +------------+
| -m_builder:Builder*|   uses   | [+] buildEngine |           | -m_engine:Engine*|
+------------------+----------| [+] buildBody   |  creates  | -m_body:Body*   |
| + Director(Builder*) |       | [+] getResult   |  -------> | + setEngine(Engine*)|
| + construct()       |       |                 |           | + setBody(Body*)   |
+------------------+          +-----------------+           | + showCar()       |
															   +------------+
						 +----------------+           +------------------+
						 |     Engine     |           |      Body        |
						 +----------------+           +------------------+
						 | -m_horsepower  |           | -m_color         |
						 | -m_type        |           | -m_style        |
						 | + show()       |           | + show()         |
						 +----------------+           +------------------+

*/





#include <iostream>
#include <string>
using namespace std;

class Engine {
public:
	void setHorsepower(int horsepower) {
		m_horsepower = horsepower;
	}

	void setFuelType(const string& fuelType) {
		m_fuelType = fuelType;
	}

	void setTransmission(const string& transmission) {
		m_transmission = transmission;
	}

	void setDrivetrain(const string& drivetrain) {
		m_drivetrain = drivetrain;
	}

	void showEngine() const {
		cout << "Horsepower: " << m_horsepower << endl;
		cout << "Fuel Type: " << m_fuelType << endl;
		cout << "Transmission: " << m_transmission << endl;
		cout << "Drivetrain: " << m_drivetrain << endl;
	}

private:
	int m_horsepower;
	string m_fuelType;
	string m_transmission;
	string m_drivetrain;
};

class Body {
public:
	void setColor(const string& color) {
		m_color = color;
	}

	void setBodyType(const string& bodyType) {
		m_bodyType = bodyType;
	}

	void setSeats(int seats) {
		m_seats = seats;
	}

	void showBody() const {
		cout << "Color: " << m_color << endl;
		cout << "Body Type: " << m_bodyType << endl;
		cout << "Seats: " << m_seats << endl;
	}

private:
	string m_color;
	string m_bodyType;
	int m_seats;
};

class Car {
public:
	void setEngine(const Engine& engine) {
		m_engine = engine;
	}

	void setBody(const Body& body) {
		m_body = body;
	}

	void showCar() const {
		cout << "Engine: " << endl;
		m_engine.showEngine();
		cout << "Body: " << endl;
		m_body.showBody();
	}

private:
	Engine m_engine;
	Body m_body;
};

class Builder {
public:
	virtual void buildEngine() = 0;
	virtual void buildBody() = 0;
	virtual Car getResult() = 0;
};

class CarBuilder : public Builder {
public:
	void buildEngine() {
		m_engine.setHorsepower(300);
		m_engine.setFuelType("Gasoline");
		m_engine.setTransmission("Automatic");
		m_engine.setDrivetrain("All-Wheel Drive");
	}

	void buildBody() {
		m_body.setColor("Black");
		m_body.setBodyType("Sedan");
		m_body.setSeats(5);
	}

	Car getResult() {
		Car car;
		car.setEngine(m_engine);
		car.setBody(m_body);
		return car;
	}

private:
	Engine m_engine;
	Body m_body;
};

class Director {
public:
	Director(Builder* builder) {
		m_builder = builder;
	}

	void construct() {
		m_builder->buildEngine();
		m_builder->buildBody();
	}

private:
	Builder* m_builder;
};

int main() {
	CarBuilder builder;
	Director director(&builder);
	director.construct();
	Car car = builder.getResult();
	car.showCar();

	//////////// output ////////////
	// Engine:
	// Horsepower: 300
	// Fuel Type: Gasoline
	// Transmission: Automatic
	// Drivetrain: All-Wheel Drive
	// Body:
	// Color: Black
	// Body Type: Sedan
	// Seats: 5
	///////////////////////////////


	return 0;
}
