#include "Enemigo.h"
#include "Constantes.h"


void Enemigo::SetSiguente(Enemigo* enemigo)
{
	_siguiente = enemigo;
}

Enemigo* Enemigo::GetSiguente()
{
	return _siguiente;
}

Enemigo::Enemigo(int Piso)
{
	_siguiente = NULL;
	
	int shell=rand()%4;
	switch(shell)
	{
		case 0:
			_textureName = "shell_amarillo.png";
			break;
		case 1:
			_textureName = "shell_azul.png";
			break;
		case 2:
			_textureName = "shell_rojo.png";
			break;
		case 3:
			_textureName = "shell_verde.png";
			break;
	}	
	_position.y = (float) C::POSICION_TERRENO_Y - (C::ALTURA_PISO * Piso);	
}

void Enemigo::Update()
{
	//TODO: Ver sentido de movimiento
	//_position.x = _position.x - 5;
	Move();	
}

void Enemigo::SetPosX(int pos_x)
{
	_pos_x = pos_x;
	_position.x -= _pos_x * _width;
	Move();
}

void Enemigo::Init()
{
	GameObject::Init();	
	_position.x -= _pos_x * _width;

	LocalFlip();
	
	Move();

	ChangeVel();
}

void Enemigo::LocalFlip()
{
	if(_isManualFlip)
	{
		 if(!_isNoFlip)
		 {
			 _isLeft = false;
			_isRight = true;
		 }
		 else
		 {
			 _isLeft = true;
			 _isRight = false;
		 }

		ManualFlip();
	}
}

void Enemigo::ChangeVel()
{
	_vel = rand()%10 + (rand()%5+3);
}

void Enemigo::MoveLeft()
{
	_position.x = _position.x - _vel;
}

void Enemigo::MoveRight()
{
	_position.x = _position.x + _vel;
}

Enemigo::~Enemigo(void)
{

}