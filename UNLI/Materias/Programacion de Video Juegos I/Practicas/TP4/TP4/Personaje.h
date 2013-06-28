#pragma once
#include "gameobject.h"
class Personaje :
	public GameObject
{
private:
	static const int POSICION_TERRENO_Y = 483;
	static const int MIN_POSICION_TERRENO_Y = -30;
	static const int MAX_ASCENSO_SALTO_Y = 90;
	static const int POSICION_PLATAFORMA_Y = 75;
	bool teclaSaltoPresionada;
	bool enAscenso;
	bool saltoEnProceso;
	float _posicion_terreno_y;
	float _max_ascenso_salto_y;
public:
	void Init();
	void InitPosition();
	virtual void Update();
	bool TestCollitions(GameObject& target);
	virtual void UpdatePoolEvents(Event& evt);
	Personaje(void);
	~Personaje(void);
};

