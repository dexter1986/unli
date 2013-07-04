#pragma once
#include "gamebase.h"
#include "QueryClass.h"
#include "Cronometro.h"

class TP4 :	public GameBase
{
private:	
	//cuerpo de box2d 
	b2Body* controlBody;
	//Nivel
	b2Body* groundWallBody[4];
	QueryDisparos _query;
	Cronometro* _cronometro;
	void ActualizarContador();

	Text text;	
	int contador;
	bool isGamePause;

	RectangleShape box;

protected:	
	virtual void DrawGame();
	virtual void UpdatePoolEvents(Event evt); 
	virtual void UpdateEvents();
	virtual void CheckCollitions();
	virtual void InitPhysics();	
	virtual void UpdatePhysics();	
	virtual void Init();
	virtual void UpdateState();
	
protected:	
	void InitSFML();
public:
	TP4(int ancho, int alto,std::string titulo);
	~TP4(void);
};


