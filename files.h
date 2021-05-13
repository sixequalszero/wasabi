
#include <filesystem>
using std::filesystem::path;

#include <string>
using std::string;

namespace wasabi::inline v1
{
	path getHome();
	string read(const path& filepath);
}