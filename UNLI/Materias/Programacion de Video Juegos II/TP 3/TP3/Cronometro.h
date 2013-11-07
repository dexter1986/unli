#pragma once
#include <SFML/Graphics.hpp>
#include "Constantes.h"

using namespace sf;

class Cronometro 
{
private:	
	int contador;
	sf::String text;	
	float tiempoInicio;
	float tiempoFin;
	int max_value;
	float final_count_seconds;
	sf::Clock _reloj;
public:
	void SetPosition(float x, float y);
	const sf::Drawable& DrawObject();
	Cronometro(int segundos,sf::Font &font);		
	void Init();	
	void Update();
	bool isEndTime();
	void Reset();
	~Cronometro(void);
};

