#pragma once
#include "Drawable.h"

class Comida : public DrawBase
{
	Texture m_img;
	Sprite m_spr;

public:
	void Draw(RenderWindow* wnd);
	Comida(void);
	~Comida(void);
	void SetPosition(Vector2f pos);
	Vector2f GetPosition();
};

