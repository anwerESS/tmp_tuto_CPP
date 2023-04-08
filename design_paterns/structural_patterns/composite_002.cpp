// Suppose you are building a software application for a furniture manufacturer. The manufacturer wants to be able to design and sell custom furniture, which can be made up of individual pieces such as chairs, tables, and sofas, as well as composite pieces such as a dining table with chairs. The manufacturer also wants to be able to calculate the cost of each custom piece based on the cost of its components.

// To implement this functionality using the Composite Design Pattern, you might define a FurniturePiece abstract base class, with subclasses IndividualPiece and CompositePiece. IndividualPiece would represent a single piece of furniture such as a chair or table, while CompositePiece would represent a composite piece of furniture made up of individual pieces.

// Each FurniturePiece object would have a price, and a calculatePrice() method that would return the total price of the piece and its components. The CompositePiece class would contain a collection of FurniturePiece objects, and its calculatePrice() method would recursively calculate the total price of all its components.

// In this example, we define FurniturePiece as the base class for both IndividualPiece and CompositePiece. IndividualPiece represents a single piece of furniture with a fixed

/*
			 +-------------------+
			 |   FurniturePiece  |
			 +-------------------+
			 | +price: double    |
			 +-------------------+
			 | calculatePrice()  |
			 +-------------------+
					/        \
				   /          \
				  /            \
   +-----------------+    +-----------------+
   | IndividualPiece |    |  CompositePiece |
   +-----------------+    +-----------------+
   |   +price: double|    |  +pieces: vector<FurniturePiece*>|
   +-----------------+    +-----------------+
						  | addPiece()      |
						  | removePiece()   |
						  | calculatePrice()|
						  +-----------------+

*/


#include <iostream>
#include <vector>
#include <algorithm>

class FurniturePiece {
public:
	virtual ~FurniturePiece() = default;
	virtual double calculatePrice() = 0;

protected:
	double price = 0.0;
};

class IndividualPiece : public FurniturePiece {
public:
	explicit IndividualPiece(double price) {
		this->price = price;
	}

	double calculatePrice() override {
		return price;
	}
};

class CompositePiece : public FurniturePiece {
public:
	void addPiece(FurniturePiece* piece) {
		pieces.push_back(piece);
	}

	void removePiece(FurniturePiece* piece) {
		auto it = std::find(pieces.begin(), pieces.end(), piece);
		if (it != pieces.end()) {
			pieces.erase(it);
		}
	}

	double calculatePrice() override {
		double total = 0.0;
		for (auto& piece : pieces) {
			total += piece->calculatePrice();
		}
		return total;
	}

private:
	std::vector<FurniturePiece*> pieces;
};

int main() {
	// Create individual pieces
	FurniturePiece* chair = new IndividualPiece(50.0);
	FurniturePiece* table = new IndividualPiece(100.0);
	FurniturePiece* sofa = new IndividualPiece(200.0);

	// Create composite pieces
	CompositePiece* diningSet = new CompositePiece();
	diningSet->addPiece(table);
	diningSet->addPiece(chair);
	diningSet->addPiece(chair);
	diningSet->addPiece(chair);

	CompositePiece* livingRoomSet = new CompositePiece();
	livingRoomSet->addPiece(sofa);
	livingRoomSet->addPiece(chair);
	livingRoomSet->addPiece(chair);
	livingRoomSet->addPiece(table);

	// Calculate prices
	double diningSetPrice = diningSet->calculatePrice();
	double livingRoomSetPrice = livingRoomSet->calculatePrice();

	std::cout << "Dining set price: $" << diningSetPrice << std::endl;
	std::cout << "Living room set price: $" << livingRoomSetPrice << std::endl;

	///////// output //////
	// Dining set price: $250
	// Living room set price: $400
	///////////////////////

	// Clean up
	delete chair;
	delete table;
	delete sofa;
	delete diningSet;
	delete livingRoomSet;

	return 0;
}
