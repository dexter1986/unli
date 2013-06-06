#include "Personaje.h"

Personaje::Personaje(void)
{
	_textureName = "jumper.png";
	_position.x = 400;
	_position.y = POSICION_TERRENO_Y;

	teclaSaltoPresionada = false;
	enAscenso = false;
	saltoEnProceso = false;
}

Personaje::~Personaje(void)
{
}

bool Personaje::TestCollitions(GameObject& target)
{
	FloatRect rect_t = target.GetBound();
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
		return true;
	}
	return false;
}

void Personaje::Init()
{
	GameObject::Init();	
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

		//Se controla cuando se llega al maximo de altura de salto
		if(_position.y <= POSICION_TERRENO_Y - MAX_ASCENSO_SALTO_Y){
			enAscenso = false;
		}

		//Se ejecuta el movimiento hacia arriba o abajo en eje y
		if(enAscenso){
			_position.y = _position.y - 5;
		}else{
			_position.y = _position.y + 5;
		}

		//Se controla cuando el personaje vuelve a tocar la eje y del terreno
		if(_position.y >= POSICION_TERRENO_Y){
			saltoEnProceso = false; //Permite que finalize un ciclo de salto y que comienze uno nuevo
			_position.y = POSICION_TERRENO_Y;//Se fuerza la posicion del personaje en la linea de terreno			
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