#include <iostream>
using std::clog;
using std::endl;

#include <type_traits>
using std::is_base_of_v;

#include <stdexcept>
using std::exception;
using std::runtime_error;
using std::invalid_argument;

#include <string>
using std::string;

#include <experimental/source_location>
using std::experimental::source_location;

template < typename type >
concept exception = is_base_of_v< exception, type >;

template < exception throwing>
[[noreturn]] inline void crash(const string& message,
	const source_location& location = source_location::current())
{	
	clog << "Exception: "
		<< location.file_name() << "("
		<< location.line() << ":"
		<< location.column() << ") `"
		<< location.function_name() << "` "
		<< message << endl;
	throw_with_nested(throwing(message));
}

[[noreturn]] inline void crash(const string& message,
	const source_location& location = source_location::current())
{	
	crash<runtime_error>(message, location);
}

inline void report(const string& message = "",
	const source_location& location = source_location::current());

void VLOG (const string&, const string&);
void ENTER(const string&, const string&);
void EXIT (const string&, const string&);
void VLOG (const string& );
void ENTER(const string& );
void EXIT (const string& );