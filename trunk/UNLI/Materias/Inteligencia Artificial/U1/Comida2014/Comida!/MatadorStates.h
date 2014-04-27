#pragma once
#include "Matador.h"
#include "Comida.h"

#define DISTANCIAVISTA 150
#define EATDIST		   10
class State_Matador_Deambular : public State<Matador>{

	private:

	//constructores vacios y por copia privados
	//para que nadie pueda crear la instancia
	State_Matador_Deambular (){}
	State_Matador_Deambular (const State_Matador_Deambular * &other){}
	State_Matador_Deambular & operator=(const State_Matador_Deambular&){}

	public:
	static State_Matador_Deambular * Instance();
	void Execute(Matador* matador);
	void Enter(Matador* matador);
	void Exit(Matador* matador);
	char* GetStateName();
	

};

class State_Matador_Perseguir : public State<Matador>{

	private:

	//constructores vacios y por copia privados
	//para que nadie pueda crear la instancia
	State_Matador_Perseguir (){}
	State_Matador_Perseguir (const State_Matador_Perseguir * &other){}
	State_Matador_Perseguir & operator=(const State_Matador_Perseguir&){}

	public:
	static State_Matador_Perseguir * Instance();
	void Execute(Matador* matador);
	void Enter(Matador* matador);
	void Exit(Matador* matador);
	char* GetStateName();
	

};