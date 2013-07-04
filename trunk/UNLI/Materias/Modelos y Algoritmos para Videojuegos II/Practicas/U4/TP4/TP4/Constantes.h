#pragma once
#include <sstream>
#include "imageManager.h"

class C
{

public:

	static float G()
	{
		return 9.8f;
	}

	template <typename T>
	static std::string NumberToString ( T Number )
	{
		ostringstream ss;
		ss << Number;
		return ss.str();
	}

	enum TipoUbicacion
	{
		Izquierda = 0,
		Derecha = 1
	};
	
};