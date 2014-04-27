#pragma once
#include <stdio.h>
#include <cassert>

template <class entity_type>
class State
{
public:
	virtual void Enter(entity_type*)=0;
	virtual void Execute(entity_type*)=0;
	virtual void Exit(entity_type*)=0;
	virtual char* GetStateName()=0;
	virtual ~State(){}
};



template <class entity_type>
class StateMachine
{
private:
	//Puntero al agente dueño de la maquina
	entity_type* m_pOwner;

	//Estado actual
	State<entity_type>* m_pCurrentState;

	//Estado previo
	State<entity_type>* m_pPreviousState;

	//Estado global
	State<entity_type>* m_pGlobalState;

public:

	StateMachine(entity_type* owner):m_pOwner(owner),
		m_pCurrentState(NULL),
		m_pPreviousState(NULL),
		m_pGlobalState(NULL)
	{}

	//Metodos para inicializar la maquina de estados
	void SetCurrentState(State<entity_type>* s){m_pCurrentState = s;}
	void SetGlobalState(State<entity_type>* s) {m_pGlobalState = s;}
	void SetPreviousState(State<entity_type>* s){m_pPreviousState = s;}

	//Metodo para actualizarla
	void Update()const
	{

		//Si hay un estado global llama su execute
		if (m_pGlobalState) m_pGlobalState->Execute(m_pOwner);

		//Igual para el estado actual
		if (m_pCurrentState) m_pCurrentState->Execute(m_pOwner);
	}

	//Metodo para cambiar de estado
	void ChangeState(State<entity_type>* pNewState)
	{
		//para asegurarnos de no cambiar a NULL
		assert(pNewState);

		//Guardamos cual era el estado anterior
		m_pPreviousState = m_pCurrentState;

		//Avisamos al actual que vamos a abandonarlo
		m_pCurrentState->Exit(m_pOwner);

		//Cambiamos al nuevo estado
		m_pCurrentState = pNewState;

		//Avisamos al nuevo estado que vamos a entrar
		m_pCurrentState->Enter(m_pOwner);
	}


	//Revertir al estado anterior
	void RevertToPreviousState()
	{
		ChangeState(m_pPreviousState);
	}

	//Accessors
	State<entity_type>* CurrentState() const{return m_pCurrentState;}
	State<entity_type>* GlobalState() const{return m_pGlobalState;}
	State<entity_type>* PreviousState() const{return m_pPreviousState;}

	//Devuelve verdadero si el estado actual es igual al que recibe
	//como parametro
	bool isInState(const State<entity_type>& st)const;

};