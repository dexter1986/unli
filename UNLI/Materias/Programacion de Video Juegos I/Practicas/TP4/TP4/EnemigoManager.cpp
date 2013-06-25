#include "EnemigoManager.h"


EnemigoManager::EnemigoManager(C::TipoUbicacion ubicacion)
{
	_head = NULL;
	_tail = NULL;
}

EnemigoManager::~EnemigoManager(void)
{

}

void EnemigoManager::Update()
{
	_head->Update();	
}

void EnemigoManager::Render(RenderWindow* app)
{
	if(_head != NULL)
	{
		Enemigo* aux = _head;
		do
		{
			app->draw(aux->DrawObject());
			aux =  aux->GetSiguente();
		}
		while(aux != NULL);
	}
}

void EnemigoManager::InvertirSentido()
{

}

Enemigo* EnemigoManager::CrearEnemigo(int Piso)
{
	return new Enemigo(Piso);
}

void EnemigoManager::DestruirEnemigo(Enemigo* enemigo)
{
	delete enemigo;
}

Enemigo* EnemigoManager::Top()
{
	return _head;
}

Enemigo* EnemigoManager::Last()
{
	return _tail;
}
	
void EnemigoManager::Encolar(Enemigo* enemigo)
{
	if(_head != NULL)
	{	
		_tail->SetSiguente(enemigo);
		_tail = enemigo;
	}
	else
	{
		_head = enemigo;
		_tail = _head;
	}
}

Enemigo* EnemigoManager::DesEncolar()
{
	Enemigo* aux = NULL;
	if(_head != NULL)
	{
		aux = _head;
		_head = _head->GetSiguente();
		if(_head == NULL)
			_tail = NULL;
	}
	return aux;
}

void EnemigoManager::Push(Enemigo* enemigo)
{
	if(_head != NULL)
	{	
		enemigo->SetSiguente(_head);
		_head = enemigo;
	}
	else
	{
		_head = enemigo;
		_tail = _head;
	}
}

Enemigo* EnemigoManager::Pop()
{
	Enemigo* aux = NULL;
	if(_head != NULL)
	{
		 aux = _head;
		_head = _head->GetSiguente();
		if(_head == NULL)
			_tail = NULL;
	}
	return aux;
}