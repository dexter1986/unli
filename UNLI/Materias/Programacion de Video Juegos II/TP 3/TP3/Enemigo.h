#pragma once
#include "personaje.h"
class Enemigo :
	public Personaje
{
protected:

	enum ModoComportamiento
	{
		GUARDIA,
		PATRULLA,
		MERCENARIO
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

	Personaje *target;
	virtual void AiNpc();

	void ModoGuardia();
	void ModoPatrulla();
	void ModoMercenario();
	void SetupComportamiento();
	bool CheckTargetVisibility();

public:
	void AiTracker(Personaje *p);
	virtual void Inicializar(ManejadorDisparos *d,Nivel *n);
	Enemigo(void);
	~Enemigo(void);
};

