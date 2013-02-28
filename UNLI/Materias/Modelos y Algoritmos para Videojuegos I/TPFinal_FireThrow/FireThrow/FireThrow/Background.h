#include "GameObject.h"
#include "NubesParallax.h"

#ifndef BACKGROUND_H
#define BACKGROUND_H

class Background : public GameObject
{
private:
	static const int MAX_WIND_FORCE = 20;
    static const int MIN_WIND_FORCE = 0;
	NubesParallax nubes;
	int windTime;
	int windNextTime;	
public:
	void InitWind();
	float wind_force;
	Background();
	void Update(RenderWindow *app);
	void Draw(RenderWindow *app);
	void Init(RenderWindow *app);
};

#endif