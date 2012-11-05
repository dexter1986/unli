#include<SFML\Window.hpp>
#include<SFML\Graphics.hpp>
#include<cstdio>
#include<iostream>

using namespace std;

#define WIDTH 800
#define HEIGTH 600

class Secuencia
{
	char sec[3];
	char evt[3];
	int count;
public:
	Secuencia();
	void Clear();
	void Agregar(sf::Event& Event);
	bool process();
};

Secuencia::Secuencia()
{
	sec[0] = 'a';
	sec[1] = 's';
	sec[2] = 'd';
	
	count = 0;
};

void Secuencia::Clear()
{
	count = 0;
};

bool Secuencia::process()
{	
	return sec[0] == evt[0] && sec[1] == evt[1] && sec[2] == evt[2];
};

void Secuencia::Agregar(sf::Event& Event)
{	
	evt[count] = Event.Key.Code;
	count++;
	if(count > 2)
		count = 0;
};

int main()
{
	sf::RenderWindow App(sf::VideoMode(WIDTH,HEIGTH,32),"Secuencias");
	const sf::Input& in = App.GetInput();
	sf::Event Event;

	sf::Image mat;
	sf::Sprite sprite;
	sf::Vector2f vect;
	Secuencia secuencia;

	mat.LoadFromFile("..\\imagenes\\cuad_blue.png");

	sprite.SetImage(mat);

	sprite.SetPosition((WIDTH - sprite.GetSize().x)/2,(HEIGTH - sprite.GetSize().y)/2);

	while(App.IsOpened())
	{	
	   
		while(App.GetEvent(Event))
		{
			if(Event.Type == sf::Event::Closed)
				App.Close();

			if(Event.Type == sf::Event::KeyPressed)
			{
				secuencia.Agregar(Event);
			}
		}	

		App.Clear();

		if(secuencia.process())
		{			
			App.Draw(sprite);
			cout<<"OK";
		}

		App.Display();

	}

	return 0;
}
