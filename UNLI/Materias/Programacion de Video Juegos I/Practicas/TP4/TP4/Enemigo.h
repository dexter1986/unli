#pragma once
#include "gameobject.h"
class Enemigo :
	public GameObject
{
private:
	Enemigo* _siguiente;
public:
	void SetSiguente(Enemigo* enemigo);
	virtual void Update();
	Enemigo* GetSiguente();
	Enemigo(int Piso);		
	~Enemigo(void);
};