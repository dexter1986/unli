#pragma once
#include "gameobject.h"

class Enemigo :
	public GameObject
{
private:
	Enemigo* _siguiente;
	int _pos_x;
	int _vel;
public:
	void SetSiguente(Enemigo* enemigo);
	void LocalFlip();
	void ChangeVel();
	void MoveLeft();
	void MoveRight();
	void SetPosX(int pos_x);
	virtual void Init();
	virtual void Update();
	Enemigo* GetSiguente();
	Enemigo(int Piso);		
	~Enemigo(void);	
};