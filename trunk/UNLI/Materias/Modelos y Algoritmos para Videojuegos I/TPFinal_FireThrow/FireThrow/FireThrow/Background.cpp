#include "Background.h"

Background::Background():GameObject(false,"..//Imagenes//Background.png")
{	
	Enable(true);
}

void Background::Init(RenderWindow *app)
{
	GameObject::Init(app);
	nubes.Init(app);
}

void Background::Update(RenderWindow *app)
{
	GameObject::Update(app);
	nubes.Update(app);
}

void Background::Draw(RenderWindow *app)
{
	GameObject::Draw(app);
	nubes.Draw(app);
}
