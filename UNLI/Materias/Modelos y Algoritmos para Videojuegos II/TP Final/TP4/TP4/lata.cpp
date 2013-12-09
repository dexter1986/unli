#include "lata.h"
#include "Constantes.h"

Lata::Lata(float sizex,float sizey,float inertia,float pos_x,float pos_y):GameObject()
{
	_textureName = "can.png";
	_sizex = sizex;
	_sizey = sizey;
	_inertia = inertia;
	_pos_x = pos_x;
	_pos_y = pos_y;
}

Lata::~Lata(void)
{

}

void Lata::Init()
{
	GameObject::Init();
	//_controlBody = PhysicManager::Instance()->CreateRectangularDynamicBody(8.0f,16.0f,0.12f,0.1f,0.2f);				
	_controlBody = PhysicManager::Instance()->CreateRectangularDynamicBody(_sizex,_sizey,0.12f,0.1f,0.2f);				
	//_controlBody->SetTransform(b2Vec2(35.0f,30.0f),0.0f);	
	_controlBody->SetTransform(b2Vec2(_pos_x,_pos_y),0.0f);	
	
	b2MassData d; 
	d.mass = 1.0f; 
	//d.I = 30.0f; 
	d.I = _inertia;
	d.center.x = 0.0f;
	d.center.y = 0.0f;

	_controlBody->SetMassData(&d);

	_controlBody->SetUserData(this);

	GameObject::InitPhysic();
}

void Lata::CheckCollitions(bool isColl)
{

}

