#pragma once
#include "Personaje.h";

class GameEngine;

class Enemigo :	public Personaje
{
protected:
	enum ModoComportamiento
	{
		GUARDIA=0,
		PATRULLA=1,
		MERCENARIO=2
	};

	enum EstadosFSM
	{
		DETENIDO,
		GIRAR,
		CORRER,
		DISPARAR,
		BUSCAR,
		CORRER_Y_DISPARAR,
		NOP
	};

	static const int MAX_DISPAROS = 10;

	EstadosFSM currentState;
	ModoComportamiento currentModo;
	int contadorPasos;
	int contadorDisparos;
	GameEngine *engine;

	Personaje *target;
	void AiNpc();

	void ModoGuardia();
	void ModoPatrulla();
	void ModoMercenario();
	void SetupComportamiento();
	bool CheckTargetVisibility();

public:
	void AiTracker(Personaje *p);
	void Inicializar(ManejadorDisparos *d,Nivel *n);
	void Inicializar();
	Enemigo(int modo,GameEngine *engine);
	~Enemigo(void);
};

