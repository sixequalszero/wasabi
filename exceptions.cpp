#include "exceptions.h"

#include <iomanip>
using std::setw;
using std::left;

namespace wasabi::inline v1
{
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
}