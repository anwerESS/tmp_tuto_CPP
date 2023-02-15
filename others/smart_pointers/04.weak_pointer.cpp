// 0. If we say unique_ptr is for unique ownership and shared_ptr is for shared ownership then
//    weak_ptr is for non-ownership smart pointer.
// 1. It actually reference to an object which is managed by shared_ptr.
// 2. A weak_ptr is created as a copy of shared_ptr.
// 3. We have to convert weak_ptr to shared_ptr in order to use the managed object.
// 4. It is used to remove cyclic dependency between shared_ptr.

#include <iostream>
#include <memory>

struct Daughter;
struct Son;

struct Mother{
	~Mother(){std::cout << "delete Mother\n";}
	void setDaughter(std::shared_ptr<Daughter> daughter){myDaughter = daughter;}
	void setSon(std::shared_ptr<Son> son){mySon = son;}
	std::weak_ptr<Daughter> myDaughter;
	std::weak_ptr<Son> mySon;
};

struct Daughter {
	Daughter(std::shared_ptr<Mother> &mother){myMother = mother;}
	~Daughter(){std::cout << "delete Daughter\n";}
	std::shared_ptr<Mother> myMother;
};

struct Son {
	Son(std::shared_ptr<Mother> &mother){myMother = mother;}
	~Son(){std::cout << "delete Son\n";}
	std::shared_ptr<Mother> myMother;
};

int main(int argc, char const *argv[])
{
	{
		std::shared_ptr<int> sh_p = std::make_shared<int>(13);
		std::shared_ptr<int> sh_p2(sh_p);
		std::weak_ptr<int> w_p1;
		std::weak_ptr<int> w_p2(w_p1);
		std::cout << w_p1.use_count() << '\n'; // 0
		std::cout << w_p2.use_count() << '\n'; // 0

		std::weak_ptr<int> w_p3(sh_p);
		w_p1 = w_p3;
		std::cout << w_p1.use_count() << '\n'; // 2
		std::cout << w_p2.use_count() << '\n'; // 0 (w_p1 reassigned and w_p2 still pointing to where w_p1 created)
		std::cout << w_p3.use_count() << '\n'; // 2
		std::cout << sh_p.use_count() << '\n'; // 2

		if(w_p2.expired() ) std::cout << "w_p2 EXPIRED\n"; // EXPIRED

		if(std::shared_ptr<int> sh_p3 = w_p1.lock()){
			std::cout << *sh_p3 << '\n'; // 13
			std::cout << w_p1.use_count() << '\n'; // 3
		} else { std::cout << "WEAK POINTER IS EXPIRED\n";}

		w_p1.reset();

		if(std::shared_ptr<int> sh_p3 = w_p1.lock()){
			std::cout << *sh_p3 << '\n';
			std::cout << w_p1.use_count() << '\n';
		} else { std::cout << "WEAK POINTER IS EXPIRED\n";} // WEAK POINTER IS EXPIRED
	}

	//--------------------------------------------------------------//
	{
		std::shared_ptr<Mother> mother 		= std::shared_ptr<Mother>( new Mother);
		std::shared_ptr<Daughter> daughter	= std::shared_ptr<Daughter>(new Daughter(mother));
		std::shared_ptr<Son> son			= std::shared_ptr<Son>(new Son(mother));
		mother->setDaughter(daughter);
		mother->setSon(son);
	}
	return 0;
}
