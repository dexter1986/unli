#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System/Clock.hpp>
#include<Box2D\Box2D.h>

#include<cstdio>
#include <tchar.h>

#include "SFMLRenderer.h"
#include "Game.h"
#include "GameImpl.h"
#include "U3_EJ1.h";
#include "U3_EJ3.h";
#include "U3_EJ6.h";

using namespace std;

int main(int argc, _TCHAR* argv[])
{
	/*GameBase *Juego;	
	Juego = new GameImpl(800,600,"Physics kit");	
	Juego->Loop();	
	delete Juego;*/

	/*U3_EJ1 u;
	u.execute();*/

	GameBase *Juego;	
	Juego = new U3_EJ6(800,600,"U3 EJ 3");	
	Juego->Loop();	
	delete Juego;

	return 0;
}

int _main(int argc, _TCHAR* argv[])
{
	sf::RenderWindow* window = new  sf::RenderWindow(sf::VideoMode(800,600),"sfml works");

	window->setFramerateLimit(30);

	sf::Clock clk;

	b2World* phyWorld = new b2World(b2Vec2(0.0f,9.8f) ,true);
	
	SFMLRenderer *debugRender = new SFMLRenderer(window);
	
	debugRender->SetFlags(UINT_MAX);

	phyWorld->SetDebugDraw(debugRender);

	b2BodyDef defCuerpo;
	b2FixtureDef adornoDef;

	defCuerpo.type = b2BodyType::b2_dynamicBody;
	defCuerpo.position = b2Vec2(100,0);
		
	b2CircleShape pelota;

	adornoDef.restitution = 0.8f;
	adornoDef.friction = 0.1f;
	adornoDef.density = 10.0f;

	pelota.m_radius = 10.0f;
	adornoDef.shape = &pelota;

  	b2Body* pCuerpo = phyWorld->CreateBody(&defCuerpo);
	b2Fixture* pAdorno = pCuerpo->CreateFixture(&adornoDef);
	
	b2BodyDef defCuerpo2;
	b2FixtureDef adornoDef2;

	defCuerpo2.type = b2BodyType::b2_staticBody;
	defCuerpo2.position = b2Vec2(0,150);
	adornoDef2.density = 10.0f;
	
	b2PolygonShape floor;
	floor.SetAsBox(150,10);
	adornoDef2.shape = &floor;	

	b2Body* pFloor = phyWorld->CreateBody(&defCuerpo2);
	b2Fixture* adornoFloor = pFloor->CreateFixture(&adornoDef2);	

	sf:View v(sf::FloatRect(0,0,200,150));

	window->setView(v);

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

		window->clear();
		phyWorld->Step(1/30.0f,4,4);
		phyWorld->ClearForces();
		phyWorld->DrawDebugData();		
		window->display();
	}

	phyWorld->DestroyBody(pFloor);
	phyWorld->DestroyBody(pCuerpo);
	delete phyWorld;
	delete debugRender;
	delete window;

	return 0;
}