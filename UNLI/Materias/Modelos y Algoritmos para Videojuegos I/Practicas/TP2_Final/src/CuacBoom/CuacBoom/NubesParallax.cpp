#include "NubesParallax.h"

NubesParallax::NubesParallax():GameObject(false,"..//Imagenes//nubes_parallax_.png")
{
	Enable(true);
	Move(-800,0);
}

void NubesParallax::Update(RenderWindow *app)
{
	if(isLeft)
	{
		pos.x-=2;
		if(pos.x == -1600)
			pos.x = -800;
	}else
	{
		pos.x+=2;
		if(pos.x == 0)
			pos.x = -800;
	}	
	Move(pos.x,pos.y);
}

void NubesParallax::Sentido(bool isLeft)
{
	NubesParallax::isLeft = isLeft;
}