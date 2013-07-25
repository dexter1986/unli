#pragma once
#include "gameobject.h"
#include "Constantes.h"

class Ventana :
	public GameObject
{
private:
	int value;
	RectangleShape* rectangle;
	Text* txt;
public:
	int GetValue();
	void ReStart();
	Ventana(void);
	void Render(RenderWindow* wnd);
	~Ventana(void);
};

