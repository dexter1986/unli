#include "GameObject.h"


#ifndef BALA_H
#define BALA_H

class Bala : public GameObject
{
private:
	int windForce;
	int sentido;
public:
	void Update(RenderWindow *app);
	void InvPosX(int value);
	Bala(Vector2f pos,Vector2f largocano,float rad,int force,float windforce);
};

#endif