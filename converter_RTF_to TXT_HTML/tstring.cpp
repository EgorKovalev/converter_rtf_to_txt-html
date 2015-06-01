#include "stdafx.h"
#include "tstring.h"

string ConvertToString(const tstring& str)
{
	return string(str.begin(), str.end());
}