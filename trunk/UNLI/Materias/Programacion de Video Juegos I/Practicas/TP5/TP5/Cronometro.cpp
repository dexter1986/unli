#include "Cronometro.h"
#include "Constantes.h"

Cronometro::Cronometro(int segundos):GameObject()
{
	contador =  segundos;
	_position.y = 330;		
	text.setFont(ImageManager::Instance()->GetFont());	
	text.setColor(Color::Black);
	text.setCharacterSize(20);
	text.setPosition(660,0);	
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
		string str = "Tiempo: 00:";
		if(final_count_seconds < 10)
			str += "0";
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

void Cronometro::ReStart()
{
	tiempoInicio = _reloj.getElapsedTime().asSeconds() + contador;
	final_count_seconds = ((int)(tiempoInicio - tiempoFin));	
}