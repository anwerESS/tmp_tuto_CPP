// 0. std::priority_queue is a container adaptor that provides constant time lookup of the 
//    largest OR smallest element.
// 1. By default std::vector is the container used inside.
// 2. Cost of insertion and extraction is logarithmic.
// 3. std::priority_queue is implemented using std::make_heap, std::push_heap, std::pop_heap functions.

#include <iostream>
#include <queue>
#include <vector>

struct Person{
	std::string name;
	int age;
};

template <typename T> void printQueue(T queue)
{
	while (!queue.empty())
	{
		std::cout << queue.top() << ' ';
		queue.pop();
	}
	std::cout << '\n';
}

int main(int argc, char const *argv[])
{
	{
		std::priority_queue<int> prio_queue;
		for(int i : {30,10,50,40,20}) {prio_queue.push(i);} // max heap
		printQueue(prio_queue); // 50 40 30 20 10
	}

	{
		int arr[] = {30,10,50,40,20};
		std::priority_queue<int, std::vector<int>, std::greater<int>> prio_queue(arr, arr + 5); // min heap
		printQueue(prio_queue); // 10 20 30 40 50
	}

	{
		auto cmp = [](Person left, Person right){return left.age < right.age;};
		std::priority_queue<Person, std::vector<Person>, decltype(cmp) > prio_queue(cmp);
		for (auto p : {Person{"anouar", 33}, Person{"sami", 45}, Person{"ali", 22}}) {prio_queue.push(p);}
		// print priority_queue
		while (!prio_queue.empty())
		{
			std::cout << prio_queue.top().name << " - " << prio_queue.top().age << '\n';
			prio_queue.pop();
		}
		/////// output ///////
		// sami - 45
		// anouar - 33
		// ali - 22
	}
	return 0;
}

