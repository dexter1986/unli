#include "Bala.h"

Bala::Bala(Vector2f pos,Vector2f largocano,float rad,int force,int windforce):GameObject(true,"..//Imagenes//Bala.png")
{
	Enable(true);
	
	if(windforce < 0)
		sentido = 1;
	else
		sentido = -1;

	//0.3 -> factor de compensacion
	Bala::windForce = abs(windforce)*0.3;

	//25 -> Factor de compensacion
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
	//Gravedad compensada 9.8 * 1000 -> factor de compensacion
	velocidad.y -= 9800 * pow(time,2);
	
	velocidad.x += windForce * sentido;

	float y = pos.y - velocidad.y * time;
	float x = pos.x + velocidad.x * time;

	Move(x,y);
}