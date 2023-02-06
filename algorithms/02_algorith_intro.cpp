/// https://hackingcpp.com/cpp/std/algorithms/intro.html

#include <iostream>
#include <vector>
#include <execution>

// Parallel Execution


int main(int argc, char const *argv[])
{
	// Parallel Execution
	{
		std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		// standard sequential sort
		std::sort(v.begin(), v.end());                             // (1)
		// sequential execution
		std::sort(std::execution::seq, v.begin(), v.end());        // (2)
		// permitting parallel execution
		std::sort(std::execution::par, v.begin(), v.end());        // (3)
		// permitting parallel and vectorized execution
		std::sort(std::execution::par_unseq, v.begin(), v.end());  // (4)
	}

	/// Iterator / Range Categories
	{
		/*
		// Category = set of supported iterator / range object operations & guarantees
		// based on common algorithm requirements (input, output, efficiency, correctness, …)
		// determined by the input range object or the host container providing the iterator

		// Sentinel (C++20)
		iterator-like position specifier; usually only used for denoting the end of a range
		supports :  == !=

		// Input
		read access to objects; advanceable to next position
		example: iterator that reads values from a file
		supports:		* ++ == !=

		// Output
		write access to objects; advanceable to next position
		example: iterator that writes values to a file
		supports :		* ++ == !=

		// Forward
		read/write access; forward traversal, no random access
		multi-pass guarantee: iterators to the same range can be used to access the same objects multiple times
		example: std::forward_list's iterators
		supports:		* ++ == !=

		// BiDirectional
		multi-pass guarantee, traversal in both directions (but no random access)
		example: std::list's iterators
		supports:		* ++ -- == !=

		// RandomAccess
		random access, but not necessarily to a contiguous memory block
		example: std::deque's iterators
		supports:		* [] ++ -- += -= - + == != < <= > >=

		// Contiguous (C++17)
		random access to contiguous memory
		example: std::vector's iterators
		supports:		* [] ++ -- += -= - + == != < <= > >=
		*/
	}


	return 0;
}
