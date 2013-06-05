#pragma once
#include "gamebase.h"
#include "Personaje.h"
#include "Bloque.h"
#include "Fondo.h"

class TP3 :	public GameBase
{
private:	
	GameObject* personaje;
	GameObject* fondo;
	GameObject* bloques[10];
	
protected:	
	virtual void DrawGame();
	virtual void UpdatePoolEvents(Event& evt); 
	virtual void UpdateEvents();
	virtual void CheckCollitions();
	virtual void InitPhysics();	
	virtual void UpdatePhysics();	
	virtual void Init();
protected:	
	void InitSFML();
public:
	TP3(int ancho, int alto,std::string titulo);
	~TP3(void);
};


