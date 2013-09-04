#include "Prince.h"


Prince::Prince(void):SpriteBase(4,"prince.png")
{
	estado_Actual = Estado::PARADO;
}

Prince::~Prince(void)
{
}

void Prince::InicializarAnimaciones()
{
	//<sprite n="1/A00.png" x="2" y="2" w="8" h="41"/>
	(animaciones+Estado::PARADO)->AddFrame(sf::IntRect(2,2,10,43),0);
}

void Prince::Internal_Mover_y_Animar()
{

}