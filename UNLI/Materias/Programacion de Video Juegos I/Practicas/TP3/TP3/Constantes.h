#pragma once
#include <sstream>
class C
{
public:
	static const int POSICION_TERRENO_Y = 500;
	static const int MAX_ASCENSO_SALTO_Y = 100;	

	template <typename T>
	static std::string NumberToString ( T Number )
	{
		ostringstream ss;
		ss << Number;
		return ss.str();
	}
};


