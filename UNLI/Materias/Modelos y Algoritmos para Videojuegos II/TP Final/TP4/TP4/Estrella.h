#pragma once
#include "gameobject.h"
class Estrella :
	public GameObject
{
private:
	float _sizex;
	float _sizey;
	float _inertia;
	float _pos_x;
	float _pos_y;

public:
	Estrella(float sizex,float sizey,float inertia,float pos_x,float pos_y);
	void Init();
	void CheckCollitions(bool isColl);
	~Estrella(void);
};
