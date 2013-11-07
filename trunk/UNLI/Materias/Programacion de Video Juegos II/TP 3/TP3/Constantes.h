#pragma once
#include <sstream>

using namespace std;

class C
{
public:
	static const int ALTURA_PISO = 75;
	static const int POSICION_TERRENO_Y = 500;
	static const int MAX_ASCENSO_SALTO_Y = 100;	
	static const int TIEMPO_JUEGO = 60; 
	static const int TIEMPO_RESPUESTA = 5; 

	template <typename T>
	static std::string NumberToString ( T Number )
	{
		ostringstream ss;
		ss << Number;
		return ss.str();
	};

	enum TipoUbicacion
	{
		Izquierda = 0,
		Derecha = 1
	};
};


