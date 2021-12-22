#ifndef FILES
#define FILES

#include <filesystem>
using std::filesystem::path;

#include <string>
using std::string;

#include<set>
using std::set;

#include<map>
using std::map;

#include <vector>
using std::vector;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <concepts>
using std::copy_constructible;

namespace wasabi::files::inline v1
{
	path getHome();
	string read(const path& filepath);

	template <typename T>
	concept isVector = requires(T t)
	{
		t.size();
		t.begin();
		t.end();
	};

	template <typename T>
	concept isString = requires(T t)
	{
		t.size();
		t.c_str();
	};

	template <typename T>
	concept hasLoad = requires(T t, ifstream& file)
		{ t.load(file); };

	template <typename T>
	concept noLoad = copy_constructible<T> && !
		( hasLoad<T> || isVector<T> || isString<T> );

	template <typename T>
	concept hasSave = requires(T t, ofstream& file)
		{ t.save(file); };

	template <typename T>
	concept noSave= copy_constructible<T> && !
		( hasSave<T> || isVector<T> || isString<T> );

	//void load(ifstream& file, hasLoad auto& POD);
	//void load(ifstream& file, noLoad  auto& POD);

	void load(ifstream& file, hasLoad auto& POD)
	{
		//VLOG("LOADING","POD.LOAD");
		POD.load(file);
	}

	void load(ifstream& file, noLoad auto& POD)
	{
		//VLOG("LOADING","POD");
		file.read(reinterpret_cast<char*>(&POD),sizeof(POD));
	}

	void load(ifstream& file, string& str);
	//void load(ifstream& file, vector<auto>& data);
	//void load(ifstream& file, vector<hasLoad auto>& data);
	//void load(ifstream& file, vector<noLoad  auto>& data);

	template <class T, typename U>
	void load(ifstream& file, set<T, U>& data);

	void load(ifstream& file, vector<auto>& data)
	{
		//VLOG("LOADING","VECTOR");
		size_t size;
		load(file, size);
		data.resize(size);

		for (auto& it : data)
			load(file, it);
	}

	//void save(ofstream& file, const hasSave auto& STRUCT);
	//void save(ofstream& file, const noSave  auto& POD);

	void save(ofstream& file, const hasSave auto& STRUCT)
	{
		//VLOG("SAVING","struct.SAVE");
		STRUCT.save(file);
		//VLOG("SAVED","struct.SAVE");
	}

	void save(ofstream& file, const noSave auto& POD)
	{
		//VLOG("SAVING","POD");
		file.write(reinterpret_cast<const char*>(&POD),sizeof(POD));
	}
	void save(ofstream& file, const string& str);
	//void save(ofstream& file, const vector<auto>& data);
	//void save(ofstream& file, const vector<hasSave auto>& data);
	//void save(ofstream& file, const vector<noSave  auto>& data);

	template <class T, typename U>
	void save(ofstream& file, const set<T, U>& data);

	void save(ofstream& file, const vector<auto>& data)
	{
		//VLOG("SAVING","VECTOR");
		auto size = data.size();
		save(file, size);

		for (auto& it : data)
			save(file, it);
	}

	void copy(auto data, ofstream& file);
	void copy(ifstream& file, auto data);

	template <class T, typename U>
	void load(ifstream& file, set<T, U>& data)
	{
		//VLOG("LOADING","SET");
		std::vector<T> v;
		load(file, v);

		for (auto& it : v)
			data.insert(it);
		//VLOG("LOADED","SET");
	}

	template <class T, typename U>
	void save(ofstream& file, const set<T, U>& data)
	{
		//VLOG("SAVING","SET");
		std::vector<T> v(data.begin(), data.end());
		save(file, v);
		//VLOG("SAVED","SET");
	}

	template <class T, typename U>
	void load(ifstream& file, map<T, U>& data)
	{
		//VLOG("LOADING","MAP");
		std::vector<T> keys;
		std::vector<U> values;;
		load(file, keys);
		load(file, values);

		auto&& key = keys.begin();
		auto&& value = values.begin();
		while(key != keys.end())
		{
			data.emplace(*key, *value);
			key++;
			value++;
		}
	}

	template <class T, typename U>
	void save(ofstream& file, map<T, U>& data)
	{
		//VLOG("SAVING","MAP");
		std::vector<T> keys;
		std::vector<U> values;;

		for(auto&& [key,value] : data)
		{
			keys.push_back(key);
			values.push_back(value);
		}

		save(file, keys);
		save(file, values);

	}
}

#endif