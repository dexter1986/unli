#pragma once
#include "gameobject.h"
class Personaje :
	public GameObject
{
private:
	static const int POSICION_TERRENO_Y = 500;
	static const int MAX_ASCENSO_SALTO_Y = 100;
	bool teclaSaltoPresionada;
	bool enAscenso;
	bool saltoEnProceso;
public:
	virtual void Update();
	virtual void UpdatePoolEvents(Event& evt);
	Personaje(void);
	~Personaje(void);
};

