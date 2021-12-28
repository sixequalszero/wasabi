#ifndef FILES
#define FILES

#include <filesystem>
using std::filesystem::path;

#include <string>
using std::string;

#include<set>
using std::set;

#include<span>
using std::span;

#include<bit>
using std::bit_cast;

#include<map>
using std::map;

#include <vector>
using std::vector;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <concepts>
using std::copy_constructible;
using std::is_trivially_copyable;

namespace wasabi::files::inline v1
{
	path getHome();

	string read(const path& filepath);

	template <typename T>
	concept hasRead = requires(T t, ifstream& file)
		{ t.read(file); };

	template <typename T>
	concept noRead = std::is_trivially_copyable<T>::value && !hasRead<T>;

	template <typename T>
	concept hasWrite = requires(T t, ofstream& file)
		{ t.write(file); };

	template <typename T>
	concept noWrite= std::is_trivially_copyable<T>::value && !hasWrite<T>;

	constexpr
	void read(ifstream& file, hasRead auto& STRUCT)
	{
		STRUCT.read(file);
	}

	constexpr
	void write(ofstream& file, const hasWrite auto& STRUCT)
	{
		STRUCT.write(file);
	}

	constexpr
	void read(ifstream& file, noRead auto& POD)
	{
		VLOG("READ POD");
		file.read(bit_cast<char*>(&POD),sizeof(POD));
	}

	constexpr
	void write(ofstream& file, const noWrite auto& POD)
	{
		VLOG("WRITE POD");
		file.write(bit_cast<const char*>(&POD),sizeof(POD));
	}
	/*
	void read(ifstream& file, string& str)
	{
		std::span data(str);
		read(file, data);
	}

	void write(ofstream& file, const string& str)
	{
		std::span data(str);
		write(file, data);
	}
*/

	void read(ifstream& file, vector<auto>& vec)
	{
		VLOG("READ SPAN");
		std::span data(vec);
		std::cout << data.size() << '\t';

		for (auto& it : data)
			std::cout << (it);

		read(file, data);
	}

	void write(ofstream& file, const vector<auto>& vec)
	{
		VLOG("WRITE SPAN");
		std::span data(vec);
		//TRIVIALLY COPIABLE BUT STILL NEEDS TO KNOW ITS SIZE
		std::cout << bit_cast<const char*>(&data);

		std::cout << sizeof(data) << '\t';
		std::cout << data.size() << '\n';

		for (auto& it : data)
			std::cout << (it);
		std::cout << '\n';
		for (auto& it : data)
			std::cout << (it);


		write(file, "SPAN");
		write(file, data);
		write(file, "SPAN");
	}

	template <class T, typename U>
	void read(ifstream& file, set<T, U>& data)
	{
		std::vector<T> v;
		read(file, v);

		for (auto& it : v)
			data.insert(it);
	}

	template <class T, typename U>
	void write(ofstream& file, const set<T, U>& data)
	{
		//std::vector<T> v(data.begin(), data.end());
		std::span spandata(data);
		write(file, spandata);
		//save(file, v);
	}

	template <class T, typename U>
	void read(ifstream& file, map<T, U>& data)
	{
		std::vector<T> keys;
		std::vector<U> values;;
		read(file, keys);
		read(file, values);

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
	void write(ofstream& file, map<T, U>& data)
	{
		std::vector<T> keys;
		std::vector<U> values;;

		for(auto&& [key,value] : data)
		{
			keys.push_back(key);
			values.push_back(value);
		}

		write(file, keys);
		write(file, values);

	}
}

#endif