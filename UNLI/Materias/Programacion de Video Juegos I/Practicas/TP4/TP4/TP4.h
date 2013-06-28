#pragma once
#include "gamebase.h"
#include "Personaje.h"
#include "Cronometro.h"
#include "Constantes.h"
#include "Fondo.h"
#include "Bloque.h"
#include "Puerta.h"
#include "EnemigoManager.h"


class TP4 :	public GameBase
{
private:	
	GameObject* cronometro;
	GameObject* personaje;
	GameObject* puerta;
	GameObject* fondo;
	GameObject* bloques[10];
	EnemigoManager* managers[9];
	
	Text text;
	Text text_piso;
	int contador;
	bool isGamePause;

	bool _is3;
	bool _is5;
	bool _is7;

	float tiempoInicio;
	float tiempoFin;
	void ActualizarContador();
protected:	
	void CrearColas(int index,C::TipoUbicacion ubicacion,int piso);
	void CrearPila(int index,C::TipoUbicacion ubicacion,int piso,bool isCreateData=false);
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


