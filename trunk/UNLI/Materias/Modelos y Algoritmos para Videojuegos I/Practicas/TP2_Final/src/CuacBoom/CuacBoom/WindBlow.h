#include "GameObject.h"


#ifndef WIND_BLOW_H
#define WIND_BLOW_H

class WindBlow : public GameObject
{
private:
	int forcelevel;
	int sentido;
	Vector2f pos_left;
	Vector2f pos_right;
public:	
	WindBlow();
	int GetForceLevel() const;
	void Update(RenderWindow *app);	
	void Init(RenderWindow *app);
	void InitWind();
};

#endif