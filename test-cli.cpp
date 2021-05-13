#include "test-exceptions.h"
#include "test-files.h"
using namespace wasabi;

#include <iostream>
using std::cout;

int main(int , char const *[])
{
	cout << "test\texceptions\t"
		<< (testExceptions()
			? "\033[38;5;034;1mpassed\033[0m\n"
			: "\033[38;5;124;1mfailed\033[0m\n"
			);

	cout << "test\tread\t"
		<< (testRead()
			? "\033[38;5;034;1mpassed\033[0m\n"
			: "\033[38;5;124;1mfailed\033[0m\n"
			);

	return 0;
}
