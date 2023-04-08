// Observer is a behavioral design pattern that lets you define a subscription mechanism to notify multiple objects about any events that happen to the object they’re observing.

#include <iostream>
#include <vector>


// Subject interface
class Subject {
public:
	virtual void attach(class Observer* observer) = 0;
	virtual void detach(class Observer* observer) = 0;
	virtual void notify() = 0;
};

// Observer interface
class Observer {
public:
	virtual void update() = 0;
};

// Concrete subject
class ConcreteSubject : public Subject {
private:
	std::vector<Observer*> observers;
	int state;
public:
	void attach(Observer* observer) {
		observers.push_back(observer);
	}
	void detach(Observer* observer) {
		for (auto it = observers.begin(); it != observers.end(); ++it) {
			if (*it == observer) {
				observers.erase(it);
				break;
			}
		}
	}
	void notify() {
		for (auto observer : observers) {
			observer->update();
		}
	}
	void setState(int state) {
		this->state = state;
		notify();
	}
	int getState() {
		return state;
	}
};


// Concrete observer
class ConcreteObserver : public Observer {
private:
	ConcreteSubject* subject;
public:
	ConcreteObserver(ConcreteSubject* subject) {
		this->subject = subject;
		subject->attach(this);
	}
	~ConcreteObserver() {
		subject->detach(this);
	}
	void update() {
		std::cout << "Observer updated. New state is " << subject->getState() << std::endl;
	}
};

// Main function
int main() {
	// Create a concrete subject
	ConcreteSubject* subject = new ConcreteSubject();

	// Create some concrete observers and attach them to the subject
	ConcreteObserver* observer1 = new ConcreteObserver(subject);
	ConcreteObserver* observer2 = new ConcreteObserver(subject);
	ConcreteObserver* observer3 = new ConcreteObserver(subject);

	// Set the state of the subject, which should trigger the observers to update
	subject->setState(1);
	////////////// output ///////////
	// Observer updated. New state is 1
	// Observer updated. New state is 1
	// Observer updated. New state is 1
	///////////////////////////////////

	// Detach an observer and set the state again
	subject->detach(observer2);
	subject->setState(2);
	////////////// output ///////////
	// Observer updated. New state is 1
	// Observer updated. New state is 1
	// Observer updated. New state is 1
	///////////////////////////////////

	// Clean up memory
	delete observer1;
	delete observer2;
	delete observer3;
	delete subject;

	return 0;
}
