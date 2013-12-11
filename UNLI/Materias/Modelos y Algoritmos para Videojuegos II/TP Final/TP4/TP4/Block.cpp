#include "Block.h"
#include "Constantes.h"

Block::Block(float sizex,float sizey,float inertia,float pos_x,float pos_y):GameObject()
{
	_textureName = "sol.png";
	_sizex = sizex;
	_sizey = sizey;
	_inertia = inertia;
	_pos_x = pos_x;
	_pos_y = pos_y;
}

Block::~Block(void)
{
}

void Block::Init(bool isDynamic)
{
	GameObject::Init();
	
	if(!isDynamic)
	{
		_controlBody = PhysicManager::Instance()->CreateRectangularStaticBody(_sizex,_sizey,1.0f,0.2f,0.1f);
	}
	else
	{
		_controlBody = PhysicManager::Instance()->CreateRectangularDynamicBody(_sizex,_sizey,1.0f,0.2f,0.1f);
	}

	_controlBody->SetTransform(b2Vec2(_pos_x,_pos_y),0.0f);	
	b2MassData d; 
	d.mass = 1.0f; 	
	d.I = _inertia;
	d.center.x = 0.0f;
	d.center.y = 0.0f;
	_controlBody->SetMassData(&d);
	_controlBody->SetUserData(this);
	GameObject::InitPhysic();
}

void Block::CheckCollitions(bool isColl)
{

}

