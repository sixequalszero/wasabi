#include "exceptions.h"

#include <iomanip>
using std::setw;
using std::left;

inline void report(const string& message,
	const source_location& location)
{		
	static int limitReports = 2000;
	if(--limitReports>0)
	{
	clog << "info: "
		<< location.file_name() << "("
		<< location.line() << ":"
		<< location.column() << ") `"
		<< location.function_name() << "` "
		<< message << endl;
	}
	else
		throw_with_nested(runtime_error("Max number of reports reached"));
}

#ifdef VERBOSE

	static int eDepth = 0;

	void VLOG(const string& message, const string& message2)
	{
		for(int i = eDepth; i >0 ; --i)
			clog << "    ";
		clog << setw(16) << left << message << message2 << endl;
	}

	void ENTER(const string& message, const string& message2)
	{
		eDepth++;
		VLOG(message, message2);
	}

	void EXIT(const string& message, const string& message2)
	{
		VLOG(message, message2);
		eDepth--;
	}

#else

	void VLOG (const string&, const string&){}
	void ENTER(const string&, const string&){}
	void EXIT (const string&, const string&){}

#endif

void VLOG (const string& message) { VLOG (""		, message); }
void ENTER(const string& message) { ENTER("ENTERING", message); }
void EXIT (const string& message) { EXIT ("EXITING" , message); }