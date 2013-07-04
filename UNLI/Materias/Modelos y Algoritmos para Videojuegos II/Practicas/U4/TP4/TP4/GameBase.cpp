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
#include "ImageManager.h"
#include "PhysicManager.h"

GameBase::GameBase(int ancho, int alto,std::string titulo)
{
	this->alto = alto;
	this->ancho = ancho;
	wnd= new RenderWindow(VideoMode(ancho,alto),titulo);
	wnd->setVisible(true);
	fps=60;
	wnd->setFramerateLimit(fps);
	frameTime=1.0f/fps;	
	EnableDebugPhysics(false);
}

void GameBase::InitWorldPhysics(){
	PhysicManager::Instance()->InitPhysics(frameTime,8,8);
	InitPhysics();
}

void GameBase::SetZoom(){
	sf::View view1(sf::FloatRect(0.0f,0.0f,ancho/4.0f,alto/4.0f));
	view1.zoom(0.9f);
	wnd->setView(view1);
}

void GameBase::Loop(){
	SetZoom();
	Init();
	InitWorldPhysics();
	while(wnd->isOpen()){		
		wnd->clear(clearColor);
		DoEvents();
		CheckCollitions();
		UpdateWorldPhysics();
		DrawWorld();
		wnd->display();
		UpdateState();
	}
}

void GameBase::DrawWorld()
{
	if(isEnableDebugPhysics)
		PhysicManager::Instance()->Draw();
	DrawGame();
}

void GameBase::UpdateWorldPhysics(){
	PhysicManager::Instance()->UpdatePhysics();
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
	PhysicManager::Instance()->EnableDebugPhysics(isEnable,wnd);
	isEnableDebugPhysics = isEnable;
}

GameBase::~GameBase(void)
{
	delete ImageManager::Instance();
	delete PhysicManager::Instance();
}

void GameBase::Draw(const Drawable& drawable)
{
	wnd->draw(drawable);
}

void GameBase::InitGameObject(GameObject& gameobject)
{

}

Vector2f GameBase::mapPixelToCoords(const Vector2i& point) const
{
	return wnd->mapPixelToCoords(point);
}
