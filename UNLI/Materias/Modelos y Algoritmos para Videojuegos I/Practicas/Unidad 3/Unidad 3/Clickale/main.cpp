#include<SFML\Window.hpp>
#include<SFML\Graphics.hpp>
#include<cstring>
#include<iostream>
#include<sstream>

#include"Enemigo.h"

using namespace std;

#define WIDTH 800
#define HEIGHT 600

int main()
{
	Enemigo *enemigos[4];
	
	sf::Image mat;
	sf::Sprite cursor;
	sf::Event Event;
	sf::String texto;
	
	int puntos = 0;
	int index = 0;
	float time_off = 0;

	srand(time(NULL));

	texto.SetFont(sf::Font::GetDefaultFont());
	texto.SetPosition(WIDTH - 100 ,10);
	texto.SetColor(sf::Color::Red);
	texto.SetStyle(sf::String::Bold);
	
	enemigos[0] = new Enemigo("..\\Img_4\\mon_1.png",WIDTH,HEIGHT);
	enemigos[1] = new Enemigo("..\\Img_4\\mon_2.png",WIDTH,HEIGHT);
	enemigos[2] = new Enemigo("..\\Img_4\\mon_3.png",WIDTH,HEIGHT);
	enemigos[3] = new Enemigo("..\\Img_4\\mon_4.png",WIDTH,HEIGHT);
	
	mat.LoadFromFile("..\\Img_4\\Crosshair.png");
	cursor.SetImage(mat);
	cursor.SetPosition(0,0);

	sf::RenderWindow App(sf::VideoMode(WIDTH,HEIGHT,32),"Crosshair");
	const sf::Input& in = App.GetInput();
	
	App.ShowMouseCursor(false);
	
	stringstream st_s;
	string str;

	st_s << puntos;
	st_s >> str;
	texto.SetText(str);

	index = rand()%4;

	while(App.IsOpened())
	{		
		while(App.GetEvent(Event))
		{
			if(Event.Type == sf::Event::Closed)
				App.Close();

			if(Event.Type == sf::Event::MouseMoved){
			
			}

			if(Event.Type == sf::Event::MouseButtonPressed)
			{
				if(Event.MouseButton.Button == sf::Mouse::Left)
					if(enemigos[index]->Hit(Event.MouseButton.X,Event.MouseButton.Y))
					{
						puntos++;

						if(puntos < 100)
						{
							st_s.clear();
							st_s << puntos;
							st_s >> str;
							texto.SetText(str);

							enemigos[index]->Random();
							index = rand()%4;
							time_off = 0;
						}
					}
			}
		}

		if(in.IsKeyDown(sf::Key::Escape))
			App.Close();

		cursor.SetPosition(in.GetMouseX() - (cursor.GetSize().x /2),in.GetMouseY()-(cursor.GetSize().y/2));
				
		time_off +=  App.GetFrameTime();
		
		if(time_off > 1.0f)
		{
			time_off = 0;
			enemigos[index]->Random();
			index = rand()%4;
		}

		App.Clear(sf::Color::Color(200,200,200));
			
		App.Draw(texto);

		if(puntos == 100)
		{				
			texto.SetText("Ganaste...!!");
			texto.SetPosition(WIDTH/2-50,HEIGHT/2-50);						
		}else
		{
			App.Draw(enemigos[index]->Draw());
		}

		App.Draw(cursor);
		
		App.Display();
	}

	delete enemigos[0];
	delete enemigos[1];
	delete enemigos[2];
	delete enemigos[3];

	return 0;
}
