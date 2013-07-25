#include "Ventana.h"

Ventana::Ventana(void)
{
	rectangle = new RectangleShape(Vector2f(200,100));
	rectangle->setFillColor(Color::White);
	rectangle->setOutlineThickness(1.0f);
	rectangle->setOutlineColor(Color::Black);
	rectangle->setPosition(300,200);

	txt = new Text();
	txt->setFont(ImageManager::Instance()->GetFont());	
	txt->setColor(Color::Black);
	txt->setCharacterSize(14);		
	txt->setPosition(305,205);		
}

Ventana::~Ventana(void)
{
	delete rectangle;
	delete txt;
}

void Ventana::ReStart()
{
	int val1 = rand()%99+1;
	int val2 = rand()%99+1;
	int val3 = rand()%99+1;
	value = val1 + val2 + val3;
	string s = "Ingrese el resultado\nde la operacion:\n\n";
	s +="\t\t" + C::NumberToString(val1) + " + " + C::NumberToString(val2) + " + " + C::NumberToString(val3) + " = "; 
	txt->setString(s);
}

void Ventana::Render(RenderWindow* wnd)
{
	wnd->draw(*rectangle);
	wnd->draw(*txt);
}

int Ventana::GetValue()
{
	return value;
}
