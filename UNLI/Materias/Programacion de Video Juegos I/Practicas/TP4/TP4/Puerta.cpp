#include "Puerta.h"
#include "Constantes.h"

Puerta::Puerta():GameObject()
{
	_textureName = "puerta.png";
	_position.y = 26;
	_position.x = 420;
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

