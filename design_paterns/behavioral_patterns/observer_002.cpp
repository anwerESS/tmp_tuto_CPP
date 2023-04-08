// Observer is a behavioral design pattern that lets you define a subscription mechanism to notify multiple objects about any events that happen to the object they’re observing.
/////////////////////////////////////////////////////////////////////////
//  we have a stock trading system that uses the Observer design pattern to keep track of the prices of various stocks and update its display components when those prices change.

// The system consists of three main components: the Subject (StockExchange), the Observers (StockDisplay), and a main function that puts everything together.

// The StockExchange class is the Subject and is responsible for fetching and updating the current stock prices. It maintains a list of Observers and notifies them whenever the prices change. The StockExchange class is also responsible for registering and removing Observers.

// The StockDisplay class is an Observer and is responsible for displaying the updated stock prices. Each instance of the StockDisplay class is associated with a specific stock, which is passed to its constructor. When the StockExchange notifies its Observers of a price change, the StockDisplay instances that are interested in that stock will update their displays with the new price.

// The main function creates an instance of the StockExchange class and registers some StockDisplay instances with it. It then sets some initial stock prices and updates them a few times to demonstrate how the system works. Finally, the main function cleans up any memory that was allocated during the system's execution.

// Overall, the Observer design pattern allows us to decouple the logic for retrieving and updating the stock prices from the logic for displaying those prices. This makes it easy to add or remove display components without affecting the underlying data retrieval and updating logic.


#include <iostream>
#include <vector>

// Forward declaration of classes
class Subject;
class Observer;

// Observer interface
class Observer {
public:
	virtual void update(Subject* subject) = 0;
};

// Subject interface
class Subject {
public:
	virtual void registerObserver(Observer* observer) = 0;
	virtual void removeObserver(Observer* observer) = 0;
	virtual void notifyObservers() = 0;
};

// Concrete subject
class StockExchange : public Subject {
private:
	std::vector<Observer*> observers;
	std::vector<std::string> stockNames;
	std::vector<double> stockPrices;
public:
	void registerObserver(Observer* observer) {
		observers.push_back(observer);
	}
	void removeObserver(Observer* observer) {
		for (auto it = observers.begin(); it != observers.end(); ++it) {
			if (*it == observer) {
				observers.erase(it);
				break;
			}
		}
	}
	void notifyObservers() {
		for (auto observer : observers) {
			observer->update(this);
		}
	}
	void setStockPrice(std::string name, double price) {
		for (int i = 0; i < stockNames.size(); i++) {
			if (stockNames[i] == name) {
				stockPrices[i] = price;
				notifyObservers();
				return;
			}
		}
		stockNames.push_back(name);
		stockPrices.push_back(price);
		notifyObservers();
	}
	std::vector<std::string> getStockNames() {
		return stockNames;
	}
	std::vector<double> getStockPrices() {
		return stockPrices;
	}
};

// Concrete observer
class StockDisplay : public Observer {
private:
	std::string name;
public:
	StockDisplay(std::string name) {
		this->name = name;
	}
	void update(Subject* subject) {
		std::vector<std::string> stockNames = ((StockExchange*)subject)->getStockNames();
		std::vector<double> stockPrices = ((StockExchange*)subject)->getStockPrices();
		for (int i = 0; i < stockNames.size(); i++) {
			if (stockNames[i] == name) {
				std::cout << "Stock price for " << name << " is now " << stockPrices[i] << std::endl;
			}
		}
	}
};

// Main function
int main() {
	// Create a stock exchange
	StockExchange* exchange = new StockExchange();

	// Create some stock displays and register them with the exchange
	StockDisplay* display1 = new StockDisplay("AAPL");
	StockDisplay* display2 = new StockDisplay("GOOG");
	StockDisplay* display3 = new StockDisplay("TSLA");
	exchange->registerObserver(display1);
	exchange->registerObserver(display2);
	exchange->registerObserver(display3);

	// Set some initial stock prices
	exchange->setStockPrice("AAPL", 150.0);
	// Stock price for AAPL is now 150
	exchange->setStockPrice("GOOG", 900.0);
	// Stock price for AAPL is now 150
	// Stock price for GOOG is now 900
	exchange->setStockPrice("TSLA", 300.0);
	// Stock price for AAPL is now 150
	// Stock price for GOOG is now 900
	// Stock price for TSLA is now 300


	// remove observer
	exchange->removeObserver(display2);


	// Update the stock prices
	exchange->setStockPrice("AAPL", 160.0);
	// Stock price for AAPL is now 160
	// Stock price for TSLA is now 300
	exchange->setStockPrice("GOOG", 950.0);
	// Stock price for AAPL is now 160
	// Stock price for TSLA is now 300
	exchange->setStockPrice("TSLA", 350.0);
	// Stock price for AAPL is now 160
	// Stock price for TSLA is now 350

	// Clean up memory
	delete display1;
	delete display2;
	delete display3;
	delete exchange;

	return 0;
}
