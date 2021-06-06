
#include <filesystem>
using std::filesystem::path;

#include <string>
using std::string;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <concepts>
using std::copy_constructible;

namespace wasabi::inline v1
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

	void load(ifstream& file, hasLoad auto& POD);
	void load(ifstream& file, noLoad auto& POD);
	void save(ofstream& file, const hasSave auto& STRUCT);
	void save(ofstream& file, const noSave auto& POD);

}