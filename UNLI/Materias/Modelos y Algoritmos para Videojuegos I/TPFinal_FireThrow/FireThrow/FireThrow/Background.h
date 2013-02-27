#include "GameObject.h"
#include "NubesParallax.h"

#ifndef BACKGROUND_H
#define BACKGROUND_H

#define MAX_FORCE 10
#define MIN_FORCE 0

class Background : public GameObject
{
private:
	NubesParallax nubes;
	int windTime;
	int windNextTime;	
public:
	void InitWind();
	int wind_force;
	Background();
	void Update(RenderWindow *app);
	void Draw(RenderWindow *app);
	void Init(RenderWindow *app);
};

#endif