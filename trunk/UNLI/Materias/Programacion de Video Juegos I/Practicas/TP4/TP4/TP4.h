#pragma once
#include "gamebase.h"
#include "Personaje.h"
#include "Cronometro.h"
#include "Constantes.h"
#include "Fondo.h"
#include "Bloque.h"
#include "Puerta.h"

class TP4 :	public GameBase
{
private:	
	GameObject* cronometro;
	GameObject* personaje;
	GameObject* puerta;
	GameObject* fondo;
	GameObject* bloques[10];
	bool _c_bloques[10];
	bool _c_ord_bloques[10];
	int _n_bloques[10];
	int _n_ord_bloques[10];
	

	Text text;
	int contador;
	bool isGamePause;

	float tiempoInicio;
	float tiempoFin;
	void ActualizarContador();
protected:	
	virtual void DrawGame();
	virtual void UpdatePoolEvents(Event& evt); 
	virtual void UpdateState();	
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


