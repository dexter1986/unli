#pragma once
#include "gamebase.h"

class TP2 :	public GameBase
{
private:
	
	//cuerpo de box2d 
	b2Body* controlBody;		
	b2Body* obstaculoBody[6];	
	//Paredes
	b2Body* groundBody;
	b2Body* groundRightBody;
	b2Body* groundLeftBody;
	b2Body* groundTopBody;
	b2Body* baseBody;
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


