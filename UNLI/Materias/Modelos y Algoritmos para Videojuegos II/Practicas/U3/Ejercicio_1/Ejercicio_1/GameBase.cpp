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
	this->alto = alto;
	this->ancho = ancho;
	wnd= new RenderWindow(VideoMode(ancho,alto),titulo);
	wnd->setVisible(true);
	fps=60;
	wnd->setFramerateLimit(fps);
	frameTime=1.0f/fps;	
	isEnableDebugPhysics = false;
}

void GameBase::InitWorldPhysics(){

	//inicializamos el mundo con la gravedad por defecto
	phyWorld = new b2World(b2Vec2(0.0f,9.8f) ,true);	
	//MyContactListener* l= new MyContactListener();
	//phyWorld->SetContactListener(l);
	//Creamos el renderer de debug y le seteamos las banderas para que dibuje TODO
	debugRender= new SFMLRenderer(wnd);
	debugRender->SetFlags(UINT_MAX);	
	phyWorld->SetDebugDraw(debugRender);
	InitPhysics();
}

//Definimos el area del mundo que veremos en nuestro juego
//Box2D tiene problemas para simular magnitudes muy grandes
void GameBase::SetZoom(){
	sf::View view1(sf::FloatRect(0.0f,0.0f,ancho/4.0f,alto/4.0f));
	view1.zoom(1.0f);
	wnd->setView(view1);
}

void GameBase::Loop(){
	SetZoom();
	InitSFML();
	InitWorldPhysics();
	while(wnd->isOpen()){		
		wnd->clear(clearColor);
		DoEvents();
		CheckCollitions();
		UpdateWorldPhysics();
		DrawWorld();
		wnd->display();
	}
}

void GameBase::DrawWorld()
{
	if(isEnableDebugPhysics)
		phyWorld->DrawDebugData();
	DrawGame();
}

void GameBase::UpdateWorldPhysics(){
	phyWorld->Step(frameTime,8,8);
	phyWorld->ClearForces();
	UpdatePhysics();
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

void GameBase::EnableDebugPhysics(bool isEnable)
{
	isEnableDebugPhysics = isEnable ;
}

GameBase::~GameBase(void)
{

}

void GameBase::Draw(const Drawable& drawable)
{
	wnd->draw(drawable);
}

void GameBase::InitSFML()
{
}

Vector2f GameBase::mapPixelToCoords(const Vector2i& point) const
{
	return wnd->mapPixelToCoords(point);
}
