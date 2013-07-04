#pragma once
#include "gamebase.h"
#include "QueryClass.h"

class TP4 :	public GameBase
{
private:	
	//cuerpo de box2d 
	b2Body* controlBody;
	b2Body* TargetBody;
	//Nivel
	b2Body* groundWallBody[13];
	QueryDisparos _query;
	
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
	TP4(int ancho, int alto,std::string titulo);
	~TP4(void);
};


