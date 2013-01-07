#include "Pato.h"

Pato::Pato(float angulo,float force):GameObject(true,"..//Imagenes//Pato.png",4)
{
	time_lastFrame = 0;
	time_CountPattern = 0;
	time_nextPattern =(float) (rand()%3+4);
	Pato::angulo = angulo;
	Pato::force = force;
	SetAnim(0,2);
	isMorir = false;
}

void Pato::Init(RenderWindow *app)
{
	estado = Estado::caer;
	
	pos.x = rand()%app->GetWidth() / 2.0f;
	pos.y = height * -1;

	Pato::Init_Pattern(estado);
	Move(pos.x,pos.y);
	
	Enable(true);
}

void Pato::Init_Pattern(Estado estado)
{
	switch(estado)
	{
	case Estado::caer:
		Pato::Init_Caer();
		break;
	case Estado::planear:
		Pato::Init_Planear();
		break;
	case Estado::morir:
		Pato::Init_Morir();
		break;
	}
}

void Pato::Init_Planear()
{

}

void Pato::Init_Caer()
{
	float ang = 0.0f;

	if(angulo == 0)
	{
		float rot = (float)(rand()%3+1);
	
		//Calculo el angulo
		if(rot == 1)
			angulo = 30;
		else if(rot == 2)
			angulo = 45;
		else if(rot == 3)
			angulo = 60;

		//Calculo angulo en radianes
		ang = angulo * 3.14f / 180;
		//Calcula si direccion	
		angulo -=90;
	}

	float _cos = cosf(ang);
	float _sin = sinf(ang);
	
	if(force == 0)
		force =(float) (rand()%20+30);

	velocidad.x = force*_cos;
	velocidad.y = force*_sin;			
	
	Rotate(angulo);
}

void Pato::Update_Pattern(Estado estado)
{
	switch(estado)
	{
	case Estado::caer:
		Pato::Update_Caer();
		break;
	case Estado::planear:
		Pato::Update_Planear();
		break;
	case Estado::morir:
		Pato::Update_Morir();
		break;
	}
}

void Pato::Update_Planear()
{	
	//Gravedad compensada 200 -> factor de compensacion
	if(velocidad.y > 0)
	{
		velocidad.y -= 200 * Pato::time_lastFrame;	
		if(velocidad.y < 0)
			velocidad.y = 0;	
	}

	if(angulo > 0)
	{
		angulo -=1;
		Rotate(angulo);		
	}
	else if(angulo < 0)
	{
		angulo +=1;
		Rotate(angulo);		
	}
		
	float y = pos.y + velocidad.y * time_lastFrame;
	float x = pos.x + velocidad.x * time_lastFrame;

	Move(x,y);

	Anim();
}

void Pato::Update_Caer()
{
	//Gravedad compensada 200 -> factor de compensacion
	velocidad.y += 15.0 * Pato::time_lastFrame;	

	float y = pos.y + velocidad.y * time_lastFrame;
	float x = pos.x + velocidad.x * time_lastFrame;

	Move(x,y);

	//Anim();
}

void Pato::Update(RenderWindow *app)
{
	time_lastFrame = app->GetFrameTime();
	time_CountPattern += time_lastFrame;

	if(estado != Estado::morir && estado != Estado::borrar && time_CountPattern > time_nextPattern)
	{
		time_CountPattern = 0;
		time_nextPattern = (float) (rand()%3+4);
					
		if(estado == Estado::caer )
		{
			estado = Estado::planear;
		}
		else if(estado == Estado::planear)
		{
			estado = Estado::caer;
		}

		Init_Pattern(estado);
	}

	Update_Pattern(Pato::estado);
}

bool Pato::Hit(int x,int y) 
{
	if(estado != Estado::morir && estado != Estado::borrar)
	{	
		if(GameObject::Hit(x,y))
		{
			estado = Estado::morir;
			Init_Pattern(estado);
			return true;
		}
		return false;
	}
	else
		return false;
}

float Pato::getAngulo()
{
	return angulo;
}

float Pato::getForce()
{
	return force;
}

Pato::Estado Pato::getEstado()
{
	return estado;
}

void Pato::Update_Morir()
{	
	if(currentframe == 3)
	{
		isMorir = true;
	}
	else if(isMorir)
	{
		estado = Estado::borrar;
		Enable(false);
	}	
	Anim();
}

void Pato::Init_Morir()
{
	SetAnim(2,4);
	currentframe = 2;
	isMorir = false;
}