#include<cstdio>

#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"

#include"U3_EJ1.h"

using namespace std;
using namespace sf;


U3_EJ1::U3_EJ1(){}

U3_EJ1::~U3_EJ1(){}

void U3_EJ1::execute()
{

	sf::RenderWindow wnd(VideoMode(800,600),"U3_EJ1");
	wnd.setFramerateLimit(30);

	sf::RectangleShape box(Vector2f(50.0f,50.0f));
		
	box.setFillColor(Color::Red);
	box.setPosition(375.0f,100.0f);
	
	Vector2f pos;
	Vector2f vel(0.0f,0.0f);
	Vector2f acc(0.0f,0.0f);
	Vector2f F(0.0f,0.0f);
	Vector2f escala(10.0f,10.0f);

	float G = 9.8f;
	float time;
	float masa = 1.0;

	Clock clk;

	clk.restart();
	
	while(wnd.isOpen())
	{
		Event evt;
		while(wnd.pollEvent(evt))
		{
			switch(evt.type)
			{
				case Event::Closed:
					wnd.close();
					break;
			}

		}


		F.y = 0;
		F.x = 0;

		if(Keyboard::isKeyPressed(Keyboard::Up))
			F.y = -20.0f;
		if(Keyboard::isKeyPressed(Keyboard::Down))
			F.y = 20.0f;
		if(Keyboard::isKeyPressed(Keyboard::Left))
			F.x = -20.0f;
		if(Keyboard::isKeyPressed(Keyboard::Right))
			F.x = 20.0f;

		//Update
		time = clk.getElapsedTime().asSeconds();
		clk.restart();

		//Calula la posicion
		pos = box.getPosition();
		pos.y = pos.y + vel.y * time;
		pos.x = pos.x + vel.x * time;
		//Calcula la aceleracion
		acc.y = (F.y/masa + G)*escala.y; 
		acc.x = (F.x/masa)*escala.x; 
		//Calcula la velocidad
		vel.y = vel.y + acc.y * time;
		vel.x = vel.x + acc.x * time;

		box.setPosition(pos);

		wnd.clear();
		wnd.draw(box);
		wnd.display();
	}

}




