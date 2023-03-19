#include <iostream>


inline  static volatile const unsigned int * function() noexcept
{
	return new unsigned int;
}

int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}
