// In this example, there are two classes: Person and Company. The Person class represents a person with a name, and the Company class represents a company that can hire employees.

// The association relationship is established through the HireEmployee method in the Company class, which takes a Person object pointer as its parameter and adds it to a vector of employees. The PrintEmployees method in the Company class then prints the names of all the employees in the vector.

// In the main function, two Person objects are created, and their addresses are passed to the acme.HireEmployee method to add them to the vector of employees in the Company object. Finally, the acme.PrintEmployees method is called to print the names of all the employees.

#include <iostream>
#include <string>
#include <vector>

class Person {
public:
	Person(const std::string& name) : name_(name) {}
	const std::string& GetName() const { return name_; }
private:
	std::string name_;
};

class Company {
public:
	void HireEmployee(Person* employee) {
		employees_.push_back(employee);
	}
	void PrintEmployees() const {
		std::cout << "Employees:" << std::endl;
		for (const auto& employee : employees_) {
			std::cout << "- " << employee->GetName() << std::endl;
		}
	}
private:
	std::vector<Person*> employees_;
};

int main() {
	Person alice("Alice");
	Person bob("Bob");
	Company acme;
	acme.HireEmployee(&alice);
	acme.HireEmployee(&bob);
	acme.PrintEmployees();
	return 0;
}
