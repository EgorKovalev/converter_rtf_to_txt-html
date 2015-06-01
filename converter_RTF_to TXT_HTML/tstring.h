#ifndef TSTRING__H
#define TSTRING__H

using namespace std;

#ifdef _UNICODE
	typedef wstring tstring;
	typedef wofstream tofstream;
	typedef wifstream tifstream;
#else
	typedef string tstring;
	typedef ofstream tofstream;
	typedef ifstream tifstream;
#endif

extern string ConvertToString(const tstring& str);

#endif