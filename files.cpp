#include "exceptions.h"
#include "files.h"

#include <filesystem>
using std::filesystem::exists;
using std::filesystem::file_size;
using std::filesystem::filesystem_error;

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include <iostream>
using std::ios;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <sstream>
using std::ostringstream;

namespace wasabi::files::inline v1
{
	path getHome()
	{
		path home = path(getenv("HOME"));

		if(home.empty())
			home = getpwuid(getuid())->pw_dir;

		if(home.empty())
			crash("Home directory not found");

		return home;
	}

	string read(const path& filepath)
	{
		uintmax_t size;

		if (exists(filepath))
			size = file_size(filepath);
		else
			crash<runtime_error>("File not found: " + filepath.string());

		ifstream file;
		file.exceptions(ifstream::failbit | ifstream::badbit);
		try
		{
			file.open(filepath.c_str(), ios::in | ifstream::binary);
		}
		catch (...)
		{
			crash<runtime_error>(
				"Can't open file " + filepath.string());
		}

		string fileContents;

		try
		{
			fileContents.resize(size);
		}
		catch (...)
		{
			ostringstream err;
			err << "Can't load " << size << " byte file into memory";
			crash<runtime_error>(err.str());
		}

		file.read(fileContents.data(), size);
		file.close();

		return fileContents;
	}

	void load(ifstream& file, hasLoad auto& POD)
	{
		VLOG("LOADING","POD.LOAD");
		POD.load(file);
	}

	void load(ifstream& file, noLoad auto& POD)
	{
		//VLOG("LOADING","POD");
		file.read(reinterpret_cast<char*>(&POD),sizeof(POD));
	}
	
	void load(ifstream& file, string& str)
	{
		//VLOG("LOADING","STRING");
		size_t size;
		load(file, size);
		str.resize(size);
		file.read(&str[0],size);
	}

	//void load(ifstream& file, vector<noLoad auto>& data)
	void load(ifstream& file, vector<auto>& data)
	{
		//VLOG("LOADING","VECTOR");
		size_t size;
		load(file, size);
		data.resize(size);

		for (auto& it : data)
			load(file, it);
	}
/*
	void load(ifstream& file, vector<hasLoad auto>& data)
	{
		//VLOG("LOADING","VECTOR.LOAD");
		size_t size;
		load(file, size);
		data.resize(size);

		for (auto& it : data)
			it.load(file);
		//VLOG("LOADED","VECTOR.LOAD");
	}
*/

	void save(ofstream& file, const hasSave auto& STRUCT)
	{
		VLOG("SAVING","struct.SAVE");
		STRUCT.save(file);
		VLOG("SAVED","struct.SAVE");
	}

	void save(ofstream& file, const noSave auto& POD)
	{
		//VLOG("SAVING","POD");
		file.write(reinterpret_cast<const char*>(&POD),sizeof(POD));
	}

	void save(ofstream& file, const string& str)
	{
		//VLOG("SAVING","STRING");
		size_t size=str.size();
		save(file, size);
		file.write(str.c_str(),size);
	}

	void save(ofstream& file, const vector<auto>& data)
	//void save(ofstream& file, const vector<noSave auto>& data)
	{
		//VLOG("SAVING","VECTOR");
		auto size = data.size();
		save(file, size);

		for (auto& it : data)
			save(file, it);
	}
/*
	void save(ofstream& file, const vector<hasSave auto>& data)
	{
		//VLOG("SAVING","VECTOR.SAVE");
		auto size = data.size();
		save(file, size);

		for (auto& it : data)
			it.save(file);
		//VLOG("SAVED","VECTOR.SAVE");
	}
*/
}