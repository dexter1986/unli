#include "Edificio.h"

Edificio::Edificio():GameObject(false,"..//Imagenes//Background.png")
{	
	Enable(true);
}

void Edificio::Init(RenderWindow *app)
{
	GameObject::Init(app);	
}

void Edificio::Update(RenderWindow *app)
{
	GameObject::Update(app);	
}

void Edificio::Draw(RenderWindow *app)
{
	GameObject::Draw(app);	
}
