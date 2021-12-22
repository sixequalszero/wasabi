#include "test-files.h"

#include <filesystem>
using namespace std::filesystem;

#include <iostream>
using std::clog;
using std::ios;

#include <fstream>
using std::ifstream;

#include "files.h"
using namespace wasabi;


namespace wasabi
{
	constexpr std::string_view passed = "\033[38;5;034;1mpassed\033[0m\n";
	constexpr std::string_view failed = "\033[38;5;124;1mfailed\033[0m\n";

	void testFiles()
	{
		auto result = testRead();
		for(size_t index=0; index<result.size(); ++index)
		{
			clog << "test\tread()\t(" << index+1 << '/' << result.size() << ")\t"
				<< (result[index] ? passed : failed);
		}
		clog << "test\tread()\t" << (result.all() ? passed : failed);
		
	}

	bitset<2> testRead()
	{
		bitset<2> result(0);

		try	//file not found
		{
			files::read(current_path()/"no-file");
		}
		catch(const std::runtime_error& e)
		{
			result[0] = (e.what() == "File not found: "
				+ (current_path()/"no-file").string());
		};

		//no file stream exception test
		//no resize test

		string test = files::read((current_path()/"test-file"));
		result[1] = (test == "contents of test file");

		return result;
	}
}