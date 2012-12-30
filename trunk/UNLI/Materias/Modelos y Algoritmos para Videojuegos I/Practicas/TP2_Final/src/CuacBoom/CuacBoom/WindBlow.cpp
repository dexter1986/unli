#include "WindBlow.h"

WindBlow::WindBlow():GameObject(false,"..//Imagenes//WindBlow.png",6)
{
	forcelevel = 0;
	sentido = 0;
}

void WindBlow::Init(RenderWindow *app)
{
	pos_right.x = app->GetWidth() - width - 20;
	pos_right.y = 200;

	pos_left.x = 20;
	pos_left.y = 200;
}

void WindBlow::InitWind()
{
	int aux = rand()%2 + 1;
	Enable(false);

	if(aux == 1)
	{
		sentido = 1;
		Move(pos_right.x,pos_right.y);
	}
	else
	{	
		sentido = -1;
		Move(pos_left.x,pos_left.y);
	}

	forcelevel = rand()%100;
	
	if(forcelevel <= 8)
		Enable(false);
	else
	{
		if(forcelevel <= 30)
		{
			if(sentido == 1)
				currentframe = 0;
			else
				currentframe = 3;
		}
		else if(forcelevel < 60)
		{
			if(sentido == 1)
				currentframe = 1;
			else
				currentframe = 4;
		}
		else if(forcelevel > 60)
		{
			if(sentido == 1)
				currentframe = 2;
			else
				currentframe = 5;
		}
		
		UpdateFrame();

		Enable(true);
	}
}

int WindBlow::GetForceLevel() const
{
	return forcelevel*sentido;
}

void WindBlow::Update(RenderWindow *app)
{		
}