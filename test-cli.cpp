#include "test-exceptions.h"
#include "test-files.h"
using namespace wasabi;

#include <iostream>
using std::cout;

int main(int , char const *[])
{
	testExceptions();
	testFiles();
	return 0;
}
