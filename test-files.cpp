#include "test-files.h"
#include "exceptions.h"

#include <filesystem>
using namespace std::filesystem;

#include <iostream>
using std::clog;
using std::ios;

#include <fstream>
using std::fstream;

#include <vector>
using std::vector;

#include <string>
using std::string;

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

	bitset<6> testRead()
	{
		bitset<6> result(0);

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



		int i = 42;
		char c = 'a';
		vector v {6, 7, 8};
		string s {"can do it"};

		{
			ofstream file;

			file.exceptions(ofstream::failbit | ofstream::badbit);
			try
			{
				file.open(current_path()/"temp-file", std::ios::out | std::ios::trunc);
			}
			catch (...)
			{
				crash<runtime_error>("Can't create temp-file");
			}




			files::write(file, i);
			files::write(file, c);
			files::write(file, v);
			//files::write(file, s);

			file.close();
		}

		int ni = 0;
		char nc = 'o';
		vector nv {0};
		string ns {""};

		{
			ifstream file;

			file.exceptions(ifstream::failbit | ifstream::badbit);
			try
			{
				file.open(current_path()/"temp-file", std::ios::in | std::ios::binary);
			}
			catch (...)
			{
				crash<runtime_error>("Can't open temp-file");
			}

			files::read(file, ni);
			files::read(file, nc);
			files::read(file, nv);
			//files::read(file, ns);

			file.close();
		}

		result[2] = (i == ni);
		result[3] = (c == nc);
		result[4] = (v == nv);
		std::cout << v[0] << "!=" << nv[0] << '\n';
		result[5] = (s == ns);

		remove( current_path()/"temp-file" );

		return result;
	}
}