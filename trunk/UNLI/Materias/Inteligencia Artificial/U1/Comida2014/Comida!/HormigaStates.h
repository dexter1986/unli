#pragma once
#include "StateMachine.h"
#include "Hormiga.h"
#include "Comida.h"

#define DISTANCIAVISTACOMIDA 150
#define DISTANCIAVISTA 100
#define EATDIST		   10

class State_Hormiga_Deambular : public State<Hormiga>{

	private:

	//constructores vacios y por copia privados
	//para que nadie pueda crear la instancia
	State_Hormiga_Deambular (){}
	State_Hormiga_Deambular (const State_Hormiga_Deambular * &other){}
	State_Hormiga_Deambular & operator=(const State_Hormiga_Deambular&){}

	public:
	static State_Hormiga_Deambular * Instance();
	void Execute(Hormiga* hormiga);
	void Enter(Hormiga* hormiga);
	void Exit(Hormiga* hormiga);
	virtual char* GetStateName();

};

class State_Hormiga_Evadir : public State<Hormiga>{

private:

	//constructores vacios y por copia privados
	//para que nadie pueda crear la instancia
	State_Hormiga_Evadir(){}
	State_Hormiga_Evadir(const State_Hormiga_Evadir * &other){}
	State_Hormiga_Evadir & operator=(const State_Hormiga_Evadir&){}

public:
	static State_Hormiga_Evadir * Instance();
	void Execute(Hormiga* hormiga);
	void Enter(Hormiga* hormiga);
	void Exit(Hormiga* hormiga);
	virtual char* GetStateName();

};

class State_Hormiga_BuscarComida : public State<Hormiga>{

private:

	//constructores vacios y por copia privados
	//para que nadie pueda crear la instancia
	State_Hormiga_BuscarComida(){}
	State_Hormiga_BuscarComida(const State_Hormiga_BuscarComida * &other){}
	State_Hormiga_BuscarComida & operator=(const State_Hormiga_BuscarComida&){}

public:
	static State_Hormiga_BuscarComida * Instance();
	void Execute(Hormiga* hormiga);
	void Enter(Hormiga* hormiga);
	void Exit(Hormiga* hormiga);
	virtual char* GetStateName();

};