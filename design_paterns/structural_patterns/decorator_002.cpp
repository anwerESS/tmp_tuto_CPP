// Suppose you are building a system for a coffee shop that offers different types of coffee. You have a Beverage class that represents any type of beverage that the coffee shop sells, and a Coffee class that extends Beverage and represents a basic cup of coffee.

// Now, the coffee shop wants to be able to offer customers the option to add different condiments to their coffee, such as milk, sugar, and whipped cream. Instead of creating a separate class for each combination of condiments, you can use the decorator pattern to dynamically add the desired condiments to a base coffee object.

// In this example, the Beverage class defines two methods: getDescription() and getCost(). The Coffee class overrides these methods to return a description of "Coffee" and a cost of 1.0.

// To add condiments to a coffee object, you can create decorator classes that extend the CondimentDecorator class, which itself extends the Beverage class. Each decorator class takes a Beverage object as a parameter in its constructor and implements the getDescription() and getCost() methods to add the cost and description of the condiment to the cost and description of the base beverage.

// For example, the Milk class extends CondimentDecorator and takes a Beverage object as a parameter in its constructor. It overrides the getDescription() method to add ", Milk" to the base beverage's description and the getCost() method to add 0.5 to the base beverage's cost.

// To create a decorated coffee object with a certain combination of condiments, you can create a Coffee object and then wrap it in one or more decorator objects, each adding a different condiment. The resulting object will have the combined cost and description of the base coffee and all the added condiments.

// This approach allows you to add new condiments to the coffee shop's offerings without having to create a separate class for each combination of condiments. Instead, you can create new decorator classes for each new condiment and mix and match them as needed to create any desired combination.


/*
+---------------------+          +---------------------+
|     Beverage        |          |   CondimentDecorator |
+---------------------+          +---------------------+
| -description :string|          | -beverage :Beverage  |
+---------------------+          +---------------------+
| +getDescription()   |<---------| +getDescription()    |
| +getCost()          |          | +getCost()           |
+---------------------+          +---------------------+
                ^                    ^
                |                    |
                |                    |
+-----------------+             +----------------+
|      Coffee     |             |      Milk      |
+-----------------+             +----------------+
|                 |             | -cost :double  |
+-----------------+             +----------------+
| +getDescription()|<--------+  | +getDescription() |
| +getCost()       |  +------+  | +getCost()        |
+-----------------+       |     |                   |
                          |     |                   |
                          |     |                   |
                      +----------------+      +-----------------+
                      |   WhipCream    |      |      Sugar      |
                      +----------------+      +-----------------+
                      | -cost :double  |      | -cost :double   |
                      +----------------+      +-----------------+
                      | +getDescription() |   | +getDescription() |
                      | +getCost()        |   | +getCost()        |
                      +-----------------+   +------------------+
*/

#include <iostream>
#include <memory>

using namespace std;

class Beverage {
public:
	virtual ~Beverage() {}
	virtual string getDescription() const = 0;
	virtual double getCost() const = 0;
};

class Coffee : public Beverage {
public:
	string getDescription() const override {
		return "Coffee";
	}

	double getCost() const override {
		return 1.0;
	}
};

class CondimentDecorator : public Beverage {
public:
	CondimentDecorator(Beverage * beverage) : beverage_(beverage) {}

	string getDescription() const override {
		return beverage_->getDescription();
	}

	double getCost() const override {
		return beverage_->getCost();
	}

protected:
	Beverage * beverage_;
};

class Milk : public CondimentDecorator {
public:
	Milk(Beverage * beverage) : CondimentDecorator(beverage) {}

	string getDescription() const override {
		return beverage_->getDescription() + ", Milk";
	}

	double getCost() const override {
		return beverage_->getCost() + 0.5;
	}
};

class Sugar : public CondimentDecorator {
public:
	Sugar(Beverage * beverage) : CondimentDecorator(beverage) {}

	string getDescription() const override {
		return beverage_->getDescription() + ", Sugar";
	}

	double getCost() const override {
		return beverage_->getCost() + 0.25;
	}
};

class Whip : public CondimentDecorator {
public:
	Whip(Beverage * beverage) : CondimentDecorator(beverage) {}

	string getDescription() const override {
		return beverage_->getDescription() + ", Whip";
	}

	double getCost() const override {
		return beverage_->getCost() + 0.75;
	}
};

int main() {
	Beverage * coffee = new Coffee();
	Beverage * coffeeWithMilk = new Milk(coffee);
	Beverage * coffeeWithMilkAndSugar = new Sugar(coffeeWithMilk);
	Beverage * coffeeWithMilkSugarAndWhip = new Whip(coffeeWithMilkAndSugar);

	cout << coffee->getDescription() << ": $" << coffee->getCost() << endl;
	cout << coffeeWithMilk->getDescription() << ": $" << coffeeWithMilk->getCost() << endl;
	cout << coffeeWithMilkAndSugar->getDescription() << ": $" << coffeeWithMilkAndSugar->getCost() << endl;
	cout << coffeeWithMilkSugarAndWhip->getDescription() << ": $" << coffeeWithMilkSugarAndWhip->getCost() << endl;

	//////////////////// output /////////////////
	// Coffee: $1
	// Coffee, Milk: $1.5
	// Coffee, Milk, Sugar: $1.75
	// Coffee, Milk, Sugar, Whip: $2.5
	/////////////////////////////////////////////

	delete coffee;
	delete coffeeWithMilk;
	delete coffeeWithMilkAndSugar;
	delete coffeeWithMilkSugarAndWhip;

	return 0;
}
