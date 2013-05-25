#pragma once
#include "gamebase.h"
#include "Box2DHelper.h"
class GameImpl :
	public GameBase
{
private:
	
	//cuerpo de box2d 
	b2Body* controlBody;
	b2Body* leftWallBody;
	b2Body* groundBody;
	b2Body* rightWallBody;

protected:
	virtual void DrawGame();
	virtual void UpdatePoolEvents(Event evt); 
	virtual void UpdateEvents();
	virtual void CheckCollitions();
	virtual void Init_Physics();
public:
	GameImpl(int ancho, int alto,std::string titulo);
	~GameImpl(void);
};

