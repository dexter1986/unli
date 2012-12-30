#include "GameObject.h"


#ifndef ENERGY_LEVEL_H
#define ENERGY_LEVEL_H

class EnergyLevel : public GameObject
{
private:
	int forcelevel;
public:	
	EnergyLevel(Vector2f pos,Vector2f cannon_size);
	void SetForceLevel(int force);
	void Update(RenderWindow *app);
	void Init(RenderWindow *app);
};

#endif