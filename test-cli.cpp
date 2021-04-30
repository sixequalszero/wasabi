#include "test-cli.h"
#include "exceptions.h"

#include <iostream>
using std::cout;

int main(int , char const *[])
{
	ENTER("main");

	try
	{
		crash("throwing test exception");
	}
	catch(const std::exception& e)
	{
		cout << "Exception caught with message '" << e.what() << "'\n";
	}
	
	EXIT("main");
	return 0;
}