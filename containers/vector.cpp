// 1. std::vector is a sequence container and also known as Dynamic Array or Array List.
// 2. Its size can grow and shrink dynamically, and no need to provide size at compile time.

// ELEMENT ACCESS
// at(), [], front(), back(), data()

// MODIFIERS:
// insert(), emplace(), push_back(), emplace_back(), pop_back(), resize(), swap(), erase(), clear()

#include <iostream>
#include <vector>

int main(int argc, char const *argv[])
{
	// constructors used in the same order as described above:
	std::vector<int> first;                                // empty vector of ints
	std::vector<int> second (4,100);                       // four ints with value 100
	std::vector<int> third (second.begin(),second.end());  // iterating through second
	std::vector<int> fourth (third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,29};
	std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	std::cout << "The contents of fifth are:";
	for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	///////////////////////// std::vector::emplace /////////////////////////////
	std::vector<int> myvector = {10,20,30};

	auto it = myvector.emplace ( myvector.begin()+1, 100 ); // 10 100 20 30
	myvector.emplace ( it, 200 ); // 10 200 100 20 30
	myvector.emplace ( myvector.end(), 300 ); //  10 200 100 20 30 300
	//### output ### myvector contains: 10 200 100 20 30 300
	/// advantage of using emplace_back() over insert :
	/// The insert function inserts an object (a full object), while emplace acts like the object's constructor and constructs the object into the sequence.
    // std::vector<Example> ve;
    // Example e("Example object 1", 1);

    // ve.push_back(e);
    // ve.push_back(Example("Example object 2", 2));
    // ve.emplace_back("Example object 3", 3);
  	//////////////////////////// std::vector::insert /////////////////////////////
	std::vector<int> v1 ({11,22,33});                       // initializer list
	v1.insert(v1.begin(), 15); // 15 11 22 33
	v1.insert(v1.begin() + 1, myints, myints + 2); //  15 16 2 11 22 33
	v1.insert(v1.end() - 1, {88,99}); //  15 16 2 11 22 88 99 33
  	//////////////////////////// std::vector::assign /////////////////////////////
	v1.assign(myints, myints + 2);
  	//////////////////////////// std::vector::data /////////////////////////////
	std::vector<int> myvect (5);
	int* p = myvect.data(); // Returns a direct pointer to the memory array used

	//////////////////// resize, reserve, capacity, size ////////
	std::vector<int> v2 ({11,22,33});
	v2.reserve(10); // SIZE : 3 ; CAPACITY : 10
	v2.resize(4,11); // SIZE : 4 ; CAPACITY : 10 {11, 11, 11, 11}
	v2.resize(22,11); // SIZE : 22 ; CAPACITY : 22
	v2.resize(3); // SIZE : 22 ; CAPACITY : 22


  	return 0;
}
