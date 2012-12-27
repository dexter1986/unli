#include "GameObject.h"

#ifndef NUBES_PARALLAX_H
#define NUBES_PARALLAX_H

class NubesParallax : public GameObject
{
private:
	bool isLeft;
public:
	void Sentido(bool isLeft);
	NubesParallax();
	void Update(RenderWindow *app);
};

#endif