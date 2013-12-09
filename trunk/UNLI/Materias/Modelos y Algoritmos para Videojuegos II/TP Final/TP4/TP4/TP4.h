#pragma once
#include <list>
#include "gamebase.h"
#include "QueryClass.h"
#include "Cronometro.h"
#include "lata.h"
#include "Fondo.h"
#include "ContactListener.h"

class TP4 :	public GameBase
{
private:	
	//cuerpo de box2d 
	Lata* lata;
	std::list<Lata*> m_latas; 
	//Nivel
	b2Body* groundWallBody[4];
	b2Body* groundTarimaBody[3];
	QueryDisparos _query;
	ContactListener _listener;
	Cronometro* _cronometro;
	Fondo* fondo;
	bool isEndGame;
	void ActualizarContador();
	void ActualizarPuntos();

	Text text;	
	Text TexPuntos;
	int contador;	
	int iPuntos;
	bool isTarima[3];

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

public:
	TP4(int ancho, int alto,std::string titulo);
	~TP4(void);
};



