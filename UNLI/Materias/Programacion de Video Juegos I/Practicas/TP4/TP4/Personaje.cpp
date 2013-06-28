#include "Personaje.h"

Personaje::Personaje(void)
{
	_textureName = "jumper.png";
	InitPosition();
}

Personaje::~Personaje(void)
{
}

void Personaje::InitPosition()
{
	_position.x = 380;
	_posicion_terreno_y = POSICION_TERRENO_Y;
	_position.y = POSICION_TERRENO_Y;
	_max_ascenso_salto_y = MAX_ASCENSO_SALTO_Y;
	teclaSaltoPresionada = false;
	enAscenso = false;
	saltoEnProceso = false;
}

bool Personaje::TestCollitions(GameObject& target)
{
	return GameObject::TestCollitions(target);
	/*FloatRect rect_t = target.GetBound();
	Vector2<float> point;

	if(_isRight)
	{
		point.x = _position.x+_width;
		point.y = _position.y;
	}
	else
	{
		point.x = _position.x;
		point.y = _position.y;
	}

	if(rect_t.contains(point))
	{
		if(saltoEnProceso && enAscenso)
			enAscenso = false;
		return true;
	}

	return false;*/
}

void Personaje::Init()
{
	GameObject::Init();	
	Size(0.7f,0.7f);
}

void Personaje::Update()
{	
	if(Keyboard::isKeyPressed(Keyboard::Left))
	{
		_position.x = _position.x - 5;
	}
	if(Keyboard::isKeyPressed(Keyboard::Right))	
	{
		_position.x = _position.x + 5;
	}

	//Se chequea si se presionó la tecla de salto y si el proceso aún no inicio.
	if(teclaSaltoPresionada && !saltoEnProceso){
		saltoEnProceso = true;
		enAscenso = true;
	}

	//Bloque que maneja el salto y su descenso a través del eje y.
	if(saltoEnProceso){
		//Se ejecuta el movimiento hacia arriba o abajo en eje y
		if(enAscenso){
			//Se controla cuando se llega al maximo de altura de salto
			if(_position.y <= _posicion_terreno_y - _max_ascenso_salto_y)
			{			
				enAscenso = false;			
			}else
			{
				_position.y = _position.y - 5;
			}
		}
		else
		{
			_position.y = _position.y + 5;
			//Se controla cuando el personaje vuelve a tocar la eje y del terreno
			if(_position.y >= _posicion_terreno_y - POSICION_PLATAFORMA_Y){
				saltoEnProceso = false; //Permite que finalize un ciclo de salto y que comienze uno nuevo
								
				if(_position.y - _max_ascenso_salto_y < 0)
				{
					_max_ascenso_salto_y = 120;
					_position.y = _posicion_terreno_y - POSICION_PLATAFORMA_Y;
				}
				else
				{
					//Se fuerza la posicion del personaje en la linea de terreno			
					_posicion_terreno_y -= POSICION_PLATAFORMA_Y;	
					_position.y = _posicion_terreno_y;
				}				
			}
		}
	}
	Move();
}

void Personaje::UpdatePoolEvents(Event& evt)
{
	if (evt.type == sf::Event::KeyPressed && evt.key.code == sf::Keyboard::Space ){
		teclaSaltoPresionada = true;
	}else if(evt.type == sf::Event::KeyReleased && evt.key.code == sf::Keyboard::Space ){
		teclaSaltoPresionada = false;
	}
}