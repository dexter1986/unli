#pragma once
#include <sstream>
class C
{
public:
	static const int ALTURA_PISO = 100;
	static const int POSICION_TERRENO_Y = 500;
	static const int MAX_ASCENSO_SALTO_Y = 100;	
	static const int TIEMPO_JUEGO = 30; 

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


