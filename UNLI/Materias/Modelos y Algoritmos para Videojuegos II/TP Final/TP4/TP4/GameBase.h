#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
#include "imageManager.h"
#include "GameObject.h"
#include "PhysicManager.h"

using namespace sf;

class GameBase
{
private:
	//Propiedades de la ventana
	int alto;
	int ancho;		
	Color clearColor;		
	
	//tiempo de frame
	float frameTime;
	int fps;
	RenderWindow *wnd;
	bool isEnableDebugPhysics;	
	void InitWorldPhysics();
	//Main game loop		
	void UpdateWorldPhysics();
	void DoEvents();	
	void SetZoom();
	void DrawWorld(); 
	bool _isGamePause;
protected:			
	void SetPause(bool isPause);
	//Main game loop
	virtual void DrawGame()=0;
	virtual void UpdatePoolEvents(Event evt)=0; 
	virtual void UpdateEvents()=0;
	virtual void CheckCollitions()=0;
	virtual void InitPhysics()=0;	
	virtual void UpdatePhysics()=0;	
	virtual void UpdateState()=0;
	virtual void Init()=0;
	void EnableDebugPhysics(bool isEnable);
	void Draw(const Drawable& drawable);
	Vector2f mapPixelToCoords(const Vector2i& point) const;
	void CreateEnemy(int x, int y);	
	void InitGameObject(GameObject& gameobject); 
public:	
	GameBase(int ancho, int alto,std::string titulo);
	virtual ~GameBase(void);
	void Loop();	
};

