#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
#include <list>

using namespace sf;
class GameBase
{
private:
	//Propiedades de la ventana
	int alto;
	int ancho;
	
	Color clearColor;

	//objetos de box2d
	
	SFMLRenderer *debugRender;

	//tiempo de frame
	float frameTime;
	int fps;
protected:
	RenderWindow *wnd;
	b2World *phyWorld;

	//Main game loop
	virtual void DrawGame()=0;
	virtual void UpdatePoolEvents(Event evt)=0; 
	virtual void UpdateEvents()=0;
	virtual void CheckCollitions()=0;
	virtual void Init_Physics()=0;	

public:
	//Constructores, destructores e inicializadores
	GameBase(int ancho, int alto,std::string titulo);
	virtual ~GameBase(void);
	void Loop();
	void CreateEnemy(int x, int y);	
	void InitPhysics();
	//Main game loop		
	void UpdatePhysics();
	void DoEvents();	
	void SetZoom();
};

