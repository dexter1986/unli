#pragma once
#include "gameobject.h"
class Cronometro :
	public GameObject
{
private:	
	int contador;
	Text text;	
	float tiempoInicio;
	float tiempoFin;
	int final_count_seconds;
	Clock _reloj;
public:
	const Drawable& DrawObject();
	Cronometro(int segundos);		
	void Init();	
	void Update();
	bool isEndTime();
	~Cronometro(void);
};

