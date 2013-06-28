#pragma once
#include "Enemigo.h"
#include "Constantes.h"

class EnemigoManager 	
{
public:
	
private:
	Enemigo* _head;
	Enemigo* _tail;
	C::TipoUbicacion _ubicacion;
	int _count;
public:	
	EnemigoManager(C::TipoUbicacion ubicacion);
	~EnemigoManager(void);

	void Update();
	void Render(RenderWindow* app);

	void InvertirSentido();
	void OrdenarPorIndex();
	C::TipoUbicacion getTipoUbicacion();

	Enemigo* CrearEnemigo(int Piso);
	void DestruirEnemigo(Enemigo* enemigo);

	Enemigo* Top();
	Enemigo* Last();
	
	void Encolar(Enemigo* enemigo);
	Enemigo* DesEncolar();

	void Push(Enemigo* enemigo);
	Enemigo* Pop();
};