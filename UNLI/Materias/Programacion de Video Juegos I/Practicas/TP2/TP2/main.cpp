#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

#include<cstdio>
#include <tchar.h>

using namespace std;

int main(int argc, _TCHAR* argv[])
{
	sf::RenderWindow* window = new  sf::RenderWindow(sf::VideoMode(800,600),"TP2");

	window->setFramerateLimit(30);

	sf::Texture *texture  = new sf::Texture();	
	texture->loadFromFile("..//Images//Personaje.png");	
	texture->setSmooth(true);

	sf::Sprite *sprite = new sf::Sprite(*texture);

	sprite->scale(0.5f,0.5f);	

	sprite->setPosition(300,200);

	sf::Vector2f pos;

	while(window->isOpen())
	{
		sf::Event evt;
		while(window->pollEvent(evt))
		{
			if(evt.type == sf::Event::Closed)
			{
				window->close();
			}
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if(sprite->getPosition().x > 2)
				sprite->move(-5,0);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if(sprite->getPosition().x < 800 - sprite->getLocalBounds().width/2)
				sprite->move(5,0);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if(sprite->getPosition().y > 2)
				sprite->move(0,-5);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if(sprite->getPosition().y < 600 - sprite->getLocalBounds().height/2)
				sprite->move(0,5);
		}
		
		window->clear(sf::Color::Black);
		window->draw(*sprite);
		window->display();
	}

	delete sprite;
	delete texture;
	delete window;

	return 0;
}