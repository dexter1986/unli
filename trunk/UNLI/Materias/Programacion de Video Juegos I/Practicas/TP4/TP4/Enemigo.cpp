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
	
	_position.y = C::ALTURA_PISO * Piso;	
}

void Enemigo::Update()
{
	//TODO: Ver sentido de movimiento
	_position.x = _position.x - 5;
	Move();
}

Enemigo::~Enemigo(void)
{

}