#include "GameObject.h"


#ifndef PATO_NEGRO_H
#define PATO_NEGRO_H

class PatoNegro : public GameObject
{
private:
	int index;
public:	
	PatoNegro(int index);
	void PatoNegro::Init(RenderWindow *app);
};

#endif