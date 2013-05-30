#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdio.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <climits>
#include "Game.h"
//#include "ContactListener.h"
#include "Box2DHelper.h"

Game::Game(int ancho, int alto,std::string titulo)
{
	wnd= new RenderWindow(VideoMode(ancho,alto),titulo);
	wnd->setVisible(true);
	fps=60;
	wnd->setFramerateLimit(fps);
	frameTime=1.0f/fps;
	SetZoom();
	InitPhysics();
}


void Game::Loop(){	
	while(wnd->isOpen()){		
		wnd->clear(clearColor);
		DoEvents();
		CheckCollitions();
		UpdatePhysics();
		DrawGame();
		wnd->display();	
	}
}

void Game::UpdatePhysics(){
	
	phyWorld->Step(frameTime,8,8);
	phyWorld->ClearForces();
	phyWorld->DrawDebugData();
}

void Game::DrawGame(){



}
void Game::DoEvents(){

	Event evt;
	while(wnd->pollEvent(evt)){	
		switch(evt.type){
			case Event::Closed:
				wnd->close();
				break;
			case Event::MouseButtonPressed:
				b2Body *body=Box2DHelper::CreateTriangularDynamicBody(phyWorld,b2Vec2(0.0f,0.0f),10.0f,1.0f,4.0f,0.1f);				
				//transformamos las coordenadas segun la vista activa
				Vector2f pos=wnd->mapPixelToCoords(sf::Vector2i(evt.mouseButton.x,evt.mouseButton.y));
				body->SetTransform(b2Vec2(pos.x,pos.y),0.0f);
				break;
		}		
	}

	//movemos el cuerpo	
	controlBody->SetAwake(true);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
		controlBody->SetLinearVelocity(b2Vec2 (-50.0f, 0.0f));
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
		controlBody->SetLinearVelocity(b2Vec2 (50.0f, 0.0f));
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
		controlBody->SetLinearVelocity(b2Vec2 (0.0f, 50.0f));
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
		controlBody->SetLinearVelocity(b2Vec2 (0.0f, -50.0f));
		
}

void Game::CheckCollitions(){

	//veremos mas adelante

}

//Definimos el area del mundo que veremos en nuestro juego
//Box2D tiene problemas para simular magnitudes muy grandes
void Game::SetZoom(){
	sf::View view1(sf::FloatRect(0.0f,0.0f,100.0f,100.0f));
	view1.zoom(1.0f);
	wnd->setView(view1);
}

void Game::InitPhysics(){

	//inicializamos el mundo con la gravedad por defecto
	phyWorld= new b2World(b2Vec2(0.0f,9.8f) ,true);
	
	//MyContactListener* l= new MyContactListener();
	//phyWorld->SetContactListener(l);
	//Creamos el renderer de debug y le seteamos las banderas para que dibuje TODO
	debugRender= new SFMLRenderer(wnd);

	debugRender->SetFlags(UINT_MAX);
	
	phyWorld->SetDebugDraw(debugRender);


	//creamos un piso y paredes
	b2Body* groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld,100,10,0,0,0);
	groundBody->SetTransform(b2Vec2(50.0f,100.0f),0.0f);

	b2Body* leftWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld,10,100,0,0,0);
	leftWallBody->SetTransform(b2Vec2(0.0f,50.0f),0.0f);

	b2Body* rightWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld,10,100,0,0,0);
	rightWallBody->SetTransform(b2Vec2(100.0f,50.0f),0.0f);
	
	//Creamos un círculo que controlaremos con el teclado
	controlBody= Box2DHelper::CreateCircularDynamicBody(phyWorld,5,1.0f,0.5,0.1f);		
	controlBody->SetTransform(b2Vec2(50.0f,50.0f),0.0f);
}


Game::~Game(void)
{
}
