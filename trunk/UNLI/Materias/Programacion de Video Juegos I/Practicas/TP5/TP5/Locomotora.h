#pragma once
#include "gameobject.h"
class Locomotora :
	public GameObject
{
private:

public:
	Locomotora();	
	void Render(RenderWindow* wnd);
	void Init();
	void Update();
	void CheckCollitions(bool isColl);
	~Locomotora(void);
};

