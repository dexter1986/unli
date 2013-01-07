#include "PatoNegro.h"

PatoNegro::PatoNegro(int index):GameObject(false,"..//Imagenes//pato_negro.png")
{
	PatoNegro::index = index;
}

void PatoNegro::Init(RenderWindow *app)
{
	 Move(app->GetWidth() / 2.0f - 100.0f - index * (width + 20.0f) , app->GetHeight() - 130.0f); 
	 Enable(true);
}