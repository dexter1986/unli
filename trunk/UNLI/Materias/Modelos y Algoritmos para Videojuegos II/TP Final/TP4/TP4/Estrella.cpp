#include "Estrella.h"
#include "Constantes.h"

Estrella::Estrella(float sizex,float sizey,float inertia,float pos_x,float pos_y):GameObject()
{
	_textureName = "estrella.png";
	_sizex = sizex;
	_sizey = sizey;
	_inertia = inertia;
	_pos_x = pos_x;
	_pos_y = pos_y;
}

Estrella::~Estrella(void)
{
}

void Estrella::Init()
{
	GameObject::Init();
	
	_controlBody = PhysicManager::Instance()->CreateRectangularKinematicBody(_sizex,_sizey);//,0.12f,0.1f,0.2f);					
	_controlBody->SetTransform(b2Vec2(_pos_x,_pos_y),0.0f);	
	
	b2MassData d; 
	d.mass = 1.0f; 	
	d.I = _inertia;
	d.center.x = 0.0f;
	d.center.y = 0.0f;
	//_controlBody->SetMassData(&d);
	_controlBody->SetUserData(this);
	GameObject::InitPhysic();
}

void Estrella::CheckCollitions(bool isColl)
{

}

