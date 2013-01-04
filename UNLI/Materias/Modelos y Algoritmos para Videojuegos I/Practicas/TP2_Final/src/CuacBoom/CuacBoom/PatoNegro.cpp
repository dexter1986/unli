#include "PatoNegro.h"

PatoNegro::PatoNegro(int index):GameObject(false,"..//Imagenes//pato_negro.png")
{
	PatoNegro::index = index;
}

void PatoNegro::Init(RenderWindow *app)
{
	 Move(app->GetWidth() / 2 - 100 - index * (width + 20) , app->GetHeight() - 130); 
	 Enable(true);
}