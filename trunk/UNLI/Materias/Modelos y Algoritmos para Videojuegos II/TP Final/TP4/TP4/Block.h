#pragma once
#include "gameobject.h"
class Block :
	public GameObject
{
private:
	float _sizex;
	float _sizey;
	float _inertia;
	float _pos_x;
	float _pos_y;

public:
	Block(float sizex,float sizey,float inertia,float pos_x,float pos_y);
	void Init(bool isDynamic=false);
	void CheckCollitions(bool isColl);
	~Block(void);
};

