#include "Background.h"

Background::Background():GameObject(false,"..//Imagenes//Background.png")
{	
	Enable(true);
}

void Background::Init(RenderWindow *app)
{
	nubes.Init(app);
	InitWind();
}

void Background::InitWind()
{
	wind_force = rand()% MAX_WIND_FORCE + MIN_WIND_FORCE;
	wind_force = rand()%2 == 0? wind_force*-1:wind_force;
	windTime = 0;
	windNextTime = rand()%5+5;	
	nubes.SetWindForce(wind_force);
}

void Background::Update(RenderWindow *app)
{
	float t = app->GetFrameTime();
	windTime += t;
	
	if(windNextTime <= windTime)
	{
		InitWind();	
	}

	nubes.Update(app);
}

void Background::Draw(RenderWindow *app)
{
	GameObject::Draw(app);
	nubes.Draw(app);
}
