#include "Helper.h"
#include <cstdio>

using namespace std;

string Helper::ToInt(int value)
{
	 ostringstream ss;
     ss << value;
     return ss.str();
}