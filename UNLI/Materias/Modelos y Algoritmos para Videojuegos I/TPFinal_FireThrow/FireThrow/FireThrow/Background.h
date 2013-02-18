#include "GameObject.h"
#include "NubesParallax.h"

#ifndef BACKGROUND_H
#define BACKGROUND_H

class Background : public GameObject
{
private:
	NubesParallax nubes;
public:
	Background();
	void Update(RenderWindow *app);
	void Draw(RenderWindow *app);
	void Init(RenderWindow *app);
};

#endif