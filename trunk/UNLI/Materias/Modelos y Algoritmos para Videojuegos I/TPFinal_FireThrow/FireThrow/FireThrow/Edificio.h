#include "GameObject.h"

#ifndef EDIFICIO_H
#define EDIFICIO_H

class Edificio : public GameObject
{
private:	
public:
	Edificio();
	void Update(RenderWindow *app);
	void Draw(RenderWindow *app);
	void Init(RenderWindow *app);
};

#endif