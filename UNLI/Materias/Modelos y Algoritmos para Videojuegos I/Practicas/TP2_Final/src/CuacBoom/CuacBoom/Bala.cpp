#include "Bala.h"

Bala::Bala(Vector2f pos,Vector2f largocano,float rad,int force):GameObject(true,"..//Imagenes//Bala.png")
{
	Enable(true);
	
	force *= 25; 

	float a = (90 + rad) * 3.14f / 180;
	float _cos = cosf(a);
	float _sin = sinf(a);

	float r =  largocano.y;
	float x = pos.x - width/2 + _cos*r;
	float y = pos.y - height/2 - _sin*r;

	velocidad.x = force*_cos;
	velocidad.y = force*_sin;

	Move(x,y);	
}

void Bala::Update(RenderWindow *app)
{
	float time = app->GetFrameTime();
	velocidad.y -= 9800 * pow(time,2);
	
	float y = pos.y - velocidad.y * time;
	float x = pos.x + velocidad.x * time;

	Move(x,y);
}