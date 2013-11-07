#include "Cronometro.h"

Cronometro::Cronometro(int segundos,sf::Font &font)
{			
	text.SetFont(font);	
	text.SetSize(10);		
	text.SetBlendMode(sf::Blend::Alpha);
	text.SetColor(Color::Color(255,255,255,210));
	max_value = segundos;	
}

Cronometro::~Cronometro(void)
{

}

void Cronometro::Update()
{	
	final_count_seconds = final_count_seconds - _reloj.GetElapsedTime();
	_reloj.Reset();
}

void Cronometro::SetPosition(float x, float y)
{
	text.SetPosition(x,y);
}

void Cronometro::Reset()
{
	_reloj.Reset();
}

void Cronometro::Init()
{
	_reloj.Reset();
	final_count_seconds = max_value;
}

const sf::Drawable& Cronometro::DrawObject()
{
	if(final_count_seconds >= 0){
		std::string str = "Time: ";		
		str += C::NumberToString((int)final_count_seconds);
		text.SetText(str);
	}
	return text;
}

bool Cronometro::isEndTime()
{
	return final_count_seconds <= 0;
}
