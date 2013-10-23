#ifndef PARALLAXLAYER_H
#define PARALLAXLAYER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class ParallaxLayer: private sf::Sprite{
private:
	// dimensiones de la imagenes
	int ancho_img, alto_img;
	// velocidad del movimiento de la capa
	float factor_x, factor_y;
	// posicion actual de la capa
	float despl_x, despl_y;
	// si es ciclica en x o en y
	bool repeat_x, repeat_y;
	// desplazamiento respecto a la vista
	float offset_x, offset_y;
	
public:
	// constructor
	ParallaxLayer(const	sf::Image &img, float factor_x, bool repeat_x=true,
									float offset_x=0, float factor_y=0,
									bool repeat_y=false, float offset_y=0);
	// mover la capa segun el tiempo
	void Move(float dt);
	// mover la capa segun el desplazamiento del personaje
	void Move(float dx, float dy);
	// dibujar la capa
	void Draw(sf::RenderWindow &w);
	// para mover las capas junto con la vista
	// en caso de usar scrolling
	void SetPosition(sf::View &v);
};

#endif

