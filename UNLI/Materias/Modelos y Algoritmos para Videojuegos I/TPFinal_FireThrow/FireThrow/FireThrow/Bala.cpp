#include "Bala.h"

Bala::Bala(Vector2f pos,Vector2f largocano,float rad,int force,float windforce):GameObject(true,"..//Imagenes//Bala.png")
{
	Enable(true);
	
	if(windforce < 0)
		sentido = 1;
	else
		sentido = -1;

	//0.3 -> factor de compensacion
	Bala::windForce =(int)(abs(windforce)*0.04);

	//40 -> Factor de compensacion
	//force *= 2;
	
	float a = (rad + 90) * 3.14f / 180;
	float _cos = cosf(a);
	float _sin = sinf(a);

	float r =  largocano.y;
	float x = pos.x - width/2 + _cos*r;
	float y = pos.y - height/2 - _sin*r;

	velocidad.x = force*_cos;
	velocidad.y = force*_sin*-1;

	Move(x,y);	
}

void Bala::InvPosX(int value)
{
	int x = 0;
	
	if(pos.x < 0)
		x = value - 10;
	else if(pos.x > 0)
		x = 10;

	Move(x,pos.y);
}

void Bala::Update(RenderWindow *app)
{
	float time = app->GetFrameTime()*6;
	
	velocidad.y += 5 * time;
	
	velocidad.x += windForce * sentido;

	float y = pos.y + velocidad.y * time;
	float x = pos.x + velocidad.x * time;

	Move(x,y);
}