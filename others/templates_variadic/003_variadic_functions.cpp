#include <iostream>
#include <stdarg.h>

int AddNumbers(int n, ...)
{
	int sum = 0;
	va_list ptr; // Declaring pointer to the argument list

	// Initializing argument to the list pointer
	va_start(ptr, n);

	for (int i = 0; i < n; i++)
		// Accessing current variable and pointing to next one
		sum += va_arg(ptr, int);
	va_end(ptr); // Ending argument list traversal

	return sum;
}

void error_log(const char * level, const char* format, ... )
{
	va_list args;
	fprintf( stderr, "[%s]: ", level);
	va_start( args, format );
	vfprintf( stderr, format, args );
	va_end( args );
	fprintf( stderr, "\n" );
}



int main(int argc, char const *argv[])
{
	//-------------------- Variadic functions AddNumbers --------------------//
	printf("\n\n Variadic functions: \n");
	printf("\n 1 + 2 = %d ",
		   AddNumbers(2, 1, 2));
	printf("\n 3 + 4 + 5 = %d ",
		   AddNumbers(3, 3, 4, 5));
	printf("\n 6 + 7 + 8 + 9 = %d ",
		   AddNumbers(4, 6, 7, 8, 9));
	printf("\n");

	//-------------------- Variadic functions write_log --------------------//
	error_log("WARNING", "Path (%s) not found at %s", "c:\\user\\Document", "2022-03-11 09:38"); // WARNING]: Path (c:\user\Document) not found at 2022-03-11 09:38
	error_log("ERROR", "An error has occured %d times due to %s", 3, "Exception"); // [ERROR]: An error has occured 3 times due to Exception




	return 0;
}
