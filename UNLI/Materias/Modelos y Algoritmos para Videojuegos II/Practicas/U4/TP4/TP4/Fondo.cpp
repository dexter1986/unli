#include "Fondo.h"


Fondo::Fondo(void)
{
	_textureName = "fondo.png";
	_position.x = 10.0f;
	_position.y = 6.5f;
}

void Fondo::Init()
{
	GameObject::Init();
	Size(0.225f,0.225f);
	
}

Fondo::~Fondo(void)
{
}
