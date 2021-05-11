#include "test-cli.h"
using namespace wasabi;

#include <iostream>
using std::cout;
using std::clog;

#include <stdexcept>
using std::invalid_argument;

int main(int , char const *[])
{

	cout << "test\texceptions\t"
		<< (testExceptions() == success::pass
			? "\033[38;5;034;1mpassed\033[0m\n"
			: "\033[38;5;124;1mfailed\033[0m\n"
			);

	return 0;
}

success testExceptions()
{
	ENTER("testExceptions");
	VLOG("testExceptions");

	try
	{
		crash("throwing exception");
	}
	catch(const std::exception& e)
	{
		clog << "Exception caught with message '" << e.what() << "'\n";
	}

	try
	{
		crash<invalid_argument>("throwing invalid_argument");
	}
	catch(const std::invalid_argument& e)
	{
		clog << "invalid_argument caught with message '" << e.what() << "'\n";
	}

	report("reporting at this position");

	EXIT("testExceptions");
	return success::pass;
}