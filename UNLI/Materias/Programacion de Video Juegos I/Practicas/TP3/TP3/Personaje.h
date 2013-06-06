#pragma once
#include "gameobject.h"
class Personaje :
	public GameObject
{
private:
	static const int POSICION_TERRENO_Y = 460;
	static const int MAX_ASCENSO_SALTO_Y = 100;
	bool teclaSaltoPresionada;
	bool enAscenso;
	bool saltoEnProceso;
public:
	void Init();
	virtual void Update();
	bool TestCollitions(GameObject& target);
	virtual void UpdatePoolEvents(Event& evt);
	Personaje(void);
	~Personaje(void);
};

