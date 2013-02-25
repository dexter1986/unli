#include "Helper.h"
#include <cstdio>

using namespace std;

string Helper::ToInt(int value)
{
	 ostringstream ss;
     ss << value;
     return ss.str();
}

int Helper::ToString(string value)
{	 
	istringstream buffer(value);
	int ret;
	buffer >> ret;
	return ret;
}