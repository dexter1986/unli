#pragma once
#include "gamebase.h"
#include "Cronometro.h"
#include "Constantes.h"
#include "Fondo.h"
#include "locomotora.h"
#include "vagon.h"
#include "Lista.h"


class TP5 :	public GameBase
{
private:	
	GameObject* cronometro;	
	GameObject* fondo;
	Lista* lista;

	Text text;
	
	int contador;
	bool isGamePause;
	float pos_x;
	float pos_y;

	float tiempoInicio;
	float tiempoFin;
	void ActualizarContador();
	void Ordenar();
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
	TP5(int ancho, int alto,std::string titulo);
	~TP5(void);
};



