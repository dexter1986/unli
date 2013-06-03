#pragma once
#include "gamebase.h"

class TP2 :	public GameBase
{
private:	
	//cuerpo de box2d 
	b2Body* controlBody;
	b2Body* TargetBody;
	//Nivel
	b2Body* groundWallBody[20];
	
	RectangleShape box;
	RectangleShape ground;
	CircleShape pelota;
protected:	
	virtual void DrawGame();
	virtual void UpdatePoolEvents(Event evt); 
	virtual void UpdateEvents();
	virtual void CheckCollitions();
	virtual void InitPhysics();	
	virtual void UpdatePhysics();	
	virtual void Init();
protected:	
	void InitSFML();
public:
	TP2(int ancho, int alto,std::string titulo);
	~TP2(void);
};


