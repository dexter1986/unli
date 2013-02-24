#include "NubesParallax.h"

NubesParallax::NubesParallax():GameObject(false,"..//Imagenes//nubes_parallax.png")
{
	windforce = 0;
	Enable(true);
	Move(-800,0);
}

void NubesParallax::Update(RenderWindow *app)
{
	float time = app->GetFrameTime();
	if(isLeft)
	{
		pos.x -= windforce * time;
		if(pos.x <= -1600)
			pos.x = -800;
	}else
	{
		pos.x += windforce * time;
		if(pos.x >= 0)
			pos.x = -800;
	}	
	Move(pos.x,pos.y);
}

void NubesParallax::Sentido(bool isLeft)
{
	NubesParallax::isLeft = isLeft;
}

void NubesParallax::SetWindForce(int force)
{
	if(force < 0)
		isLeft = false;
	else
		isLeft = true;

	windforce = abs(force);
}