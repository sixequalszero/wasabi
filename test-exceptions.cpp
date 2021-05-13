#include "test-exceptions.h"

#include <iostream>
using std::clog;

#include <stdexcept>
using std::invalid_argument;

#include <bitset>
using std::bitset;

namespace wasabi
{

	constexpr std::string_view passed = "\033[38;5;034;1mpassed\033[0m\n";
	constexpr std::string_view failed = "\033[38;5;124;1mfailed\033[0m\n";

	void testExceptions()
	{
		bitset<2> result(0);

		ENTER("testExceptions");
		VLOG("testExceptions");

		constexpr std::string_view err = "throwing exception";
		try
		{
			crash(string(err));
		}
		catch(const std::exception& e)
		{
			result[0] = (e.what() == err);
		}

		constexpr std::string_view err_arg = "throwing invalid_argument";
		try
		{
			crash<invalid_argument>(string(err_arg));
		}
		catch(const std::invalid_argument& e)
		{
			result[1] = (e.what() == err_arg);
		}

		report("reporting at this position");

		EXIT("testExceptions");
		

		for(int index=0; index<result.size(); ++index)
		{
			clog << "test\texceptions\t(" << index+1 << '/' << result.size() << ")\t"
				<< (result[index] ? passed : failed);
		}
		clog << "test\texceptions\t" << (result.all() ? passed : failed);

	}

}