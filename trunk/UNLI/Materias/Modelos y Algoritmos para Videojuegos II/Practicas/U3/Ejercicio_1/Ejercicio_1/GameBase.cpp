#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdio.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <climits>
#include "GameBase.h"
//#include "ContactListener.h"
#include "Box2DHelper.h"

GameBase::GameBase(int ancho, int alto,std::string titulo)
{
	wnd= new RenderWindow(VideoMode(ancho,alto),titulo);
	wnd->setVisible(true);
	fps=60;
	wnd->setFramerateLimit(fps);
	frameTime=1.0f/fps;	
}

void GameBase::Loop(){
	SetZoom();
	InitPhysics();
	while(wnd->isOpen()){		
		wnd->clear(clearColor);
		DoEvents();
		CheckCollitions();
		UpdatePhysics();
		DrawGame();
		wnd->display();
	}
}

void GameBase::UpdatePhysics(){
	phyWorld->Step(frameTime,8,8);
	phyWorld->ClearForces();
	phyWorld->DrawDebugData();
}

void GameBase::DoEvents(){
	Event evt;
	while(wnd->pollEvent(evt)){	
		switch(evt.type){
			case Event::Closed:
				wnd->close();
				break;			
		}
		UpdatePoolEvents(evt);
	}

	UpdateEvents();
	
		
}

//Definimos el area del mundo que veremos en nuestro juego
//Box2D tiene problemas para simular magnitudes muy grandes
void GameBase::SetZoom(){
	sf::View view1(sf::FloatRect(0.0f,0.0f,100.0f,100.0f));
	view1.zoom(1.0f);
	wnd->setView(view1);
}

void GameBase::InitPhysics(){

	//inicializamos el mundo con la gravedad por defecto
	phyWorld = new b2World(b2Vec2(0.0f,9.8f) ,true);
	
	//MyContactListener* l= new MyContactListener();
	//phyWorld->SetContactListener(l);
	//Creamos el renderer de debug y le seteamos las banderas para que dibuje TODO
	debugRender= new SFMLRenderer(wnd);

	debugRender->SetFlags(UINT_MAX);
	
	phyWorld->SetDebugDraw(debugRender);

	Init_Physics();

}


GameBase::~GameBase(void)
{

}

