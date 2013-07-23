#include "Locomotora.h"
#include "Constantes.h"

Locomotora::Locomotora():GameObject()
{
	_textureName = "locomotora.png";
	_position.y = 53.0f;
	_position.x = 200.0f;
	_isManualFlip =  true;
}

Locomotora::~Locomotora(void)
{

}

void Locomotora::Init()
{
	GameObject::Init();	
}

void Locomotora::Update()
{
	Move();
}

void Locomotora::Render(RenderWindow* wnd)
{
	wnd->draw(DrawObject());
}

void Locomotora::CheckCollitions(bool isColl)
{

}

