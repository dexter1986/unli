#include "Puerta.h"
#include "Constantes.h"

Puerta::Puerta():GameObject()
{
	_textureName = "puerta.png";
	_position.y = 26.0f;
	_position.x = 200.0f + rand()%300 + rand()%200;
}

Puerta::~Puerta(void)
{

}

void Puerta::Init()
{
	GameObject::Init();	
}

void Puerta::CheckCollitions(bool isColl)
{

}

