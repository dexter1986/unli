#include "Cronometro.h"
#include "Constantes.h"


Cronometro::Cronometro(int segundos):GameObject()
{
	_position.y = 330;		
	text.setFont(ImageManager::Instance()->GetFont());	
	text.setCharacterSize(22);
	text.scale(0.25f,0.25f);
	text.setPosition(150.0f,8.0f);	
	tiempoInicio = _reloj.getElapsedTime().asSeconds() + segundos;
	final_count_seconds = ((int)(tiempoInicio - tiempoFin));	
}

Cronometro::~Cronometro(void)
{

}

void Cronometro::Update()
{
	tiempoFin = _reloj.getElapsedTime().asSeconds();	
	final_count_seconds = ((int)(tiempoInicio - tiempoFin));
	if(final_count_seconds >= 0){
		string str = "Tiempo: ";					
		str += C::NumberToString(final_count_seconds);
		text.setString(str);
	}	
}

void Cronometro::Init()
{
	GameObject::Init();
}

const Drawable& Cronometro::DrawObject()
{
	return text;
}

bool Cronometro::isEndTime()
{
	return final_count_seconds <= 0;
}
