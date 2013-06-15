#pragma once
#include "gameobject.h"
class Puerta :
	public GameObject
{
private:

public:
	Puerta();	
	void Init();
	void CheckCollitions(bool isColl);
	~Puerta(void);
};

