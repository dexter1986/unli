#include "EnemigoManager.h"


EnemigoManager::EnemigoManager(C::TipoUbicacion ubicacion)
{
	_ubicacion = ubicacion;
	_head = NULL;
	_tail = NULL;
	_count = 0;
}

EnemigoManager::~EnemigoManager(void)
{
	if(_head != NULL)
	{
		Enemigo* aux = _head;
		do
		{
			_head =  aux->GetSiguente();
			delete aux;
			aux = _head;
		}
		while(_head != NULL);
	}
}

void EnemigoManager::Update()
{
	if(_head != NULL)
	{
		if(_ubicacion == C::TipoUbicacion::Derecha)
		{
			_head->MoveLeft();
		}
		else if(_ubicacion == C::TipoUbicacion::Izquierda)
		{
			_head->MoveRight();
		}
		_head->Update();	
	}
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
	Enemigo* aux = new Enemigo(Piso);
	aux->_isManualFlip = true;
	if(_ubicacion == C::TipoUbicacion::Izquierda)
		aux->_isNoFlip = true;	
	return aux;
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
	enemigo->SetSiguente(NULL);
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

	OrdenarPorIndex();
	_count++;
	enemigo->ChangeVel();
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

		OrdenarPorIndex();
		_count--;			
	}
	
	return aux;
}

void EnemigoManager::OrdenarPorIndex()
{
	int cont = _count;
	Enemigo* aux = _head;
	if(aux != NULL)
	{
		do
		{
			if(_ubicacion == C::TipoUbicacion::Derecha)
			{	
				Vector2f v = aux->GetPosition();
				aux->SetPosition(770,v.y);
				aux->SetPosX(cont);
			}else
			{
				Vector2f v = aux->GetPosition();
				aux->SetPosition(0,v.y);
				aux->SetPosX(-cont);
			}
			aux = aux->GetSiguente();
			cont--;
		}while(aux != NULL);
	}
}

void EnemigoManager::Push(Enemigo* enemigo)
{
	enemigo->SetSiguente(NULL);
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
	OrdenarPorIndex();
	_count++;
	if(_ubicacion == C::TipoUbicacion::Izquierda)
	{
		enemigo->_isNoFlip = true;
	}
	else
	{
		enemigo->_isNoFlip = false;
	}
	enemigo->LocalFlip();
	enemigo->Move();
	enemigo->ChangeVel();
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
		
		_count--;
	}
	
	return aux;
}

C::TipoUbicacion EnemigoManager::getTipoUbicacion()
{
	return _ubicacion;
}