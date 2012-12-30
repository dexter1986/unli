#include "EnergyLevel.h"


EnergyLevel::EnergyLevel(Vector2f pos,Vector2f cannon_size):GameObject(false,"..//Imagenes//Energia.png",5)
{
	Enable(true);
	float x = pos.x + cannon_size.x / 2 - width / 2;
	float y = pos.y + cannon_size.y / 2 - height / 2;
	Move(x,y);
}

void EnergyLevel::Init(RenderWindow *app)
{

}

void EnergyLevel::Update(RenderWindow *app)
{

}

void EnergyLevel::SetForceLevel(int force)
{
	forcelevel = force;	

	if(forcelevel == 0)			
		currentframe = 0;
	else if(forcelevel < 10)			
		currentframe = 1;
	else if(forcelevel < 20)					
		currentframe = 2;
	else if(forcelevel < 30)					
		currentframe = 3;
	else if(forcelevel == 40)					
		currentframe = 4;	

	UpdateFrame();
}
