#include "GameObject.h"


#ifndef BALA_H
#define BALA_H

class Bala : public GameObject
{
public:
	void Update(RenderWindow *app);
	Bala(Vector2f pos,Vector2f largocano,float rad,int force);
};

#endif