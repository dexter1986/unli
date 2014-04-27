#include "HormigaStates.h"
#include "Tablero.h"
#include "utils.h"
State_Hormiga_Deambular*  State_Hormiga_Deambular::Instance(){
		static State_Hormiga_Deambular instance;
		return &instance;
}

/////////////////////////////////////////////////////////////////////////////
//Deambular
/////////////////////////////////////////////////////////////////////////////

void State_Hormiga_Deambular::Enter(Hormiga* hormiga){


}

void State_Hormiga_Deambular::Execute(Hormiga* hormiga){

	Tablero* t = hormiga->GetTablero();

	//Calculamos si hay que cambiar de estado
	//vemos si hay alimento cerca
	Comida *c = t->GetNearestVisibleFood(hormiga);
	if (c != NULL){
		float dist = Utils::GetVecDistance(c->GetPosition(), hormiga->GetPosition());
		if (dist < DISTANCIAVISTACOMIDA)//cambiamos al estado de buscar comida
			hormiga->GetFSM()->ChangeState(State_Hormiga_BuscarComida::Instance());
	}

	//si vemos un matador lo evadimos
	Matador *m = t->GetClosestMatador(hormiga);
	if (m != NULL){
		float dist = Utils::GetVecDistance(m->GetPosition(), hormiga->GetPosition());
		if (dist < DISTANCIAVISTA)
			hormiga->GetFSM()->ChangeState(State_Hormiga_Evadir::Instance());
	}

	//calculamos si vamos a cambiar de dirección
	if (Utils::GetRandomIntValue(0, 100) == 0){
		hormiga->ChangeDirection();
	}
	
	hormiga->Move();
}

void State_Hormiga_Deambular::Exit(Hormiga* hormiga){


}

char* State_Hormiga_Deambular::GetStateName(){
	return "Deambular";
}

State_Hormiga_Evadir*  State_Hormiga_Evadir::Instance(){
	static State_Hormiga_Evadir instance;
	return &instance;
}

/////////////////////////////////////////////////////////////////////////////
//Evadir
/////////////////////////////////////////////////////////////////////////////

void State_Hormiga_Evadir::Enter(Hormiga* hormiga){


}

void State_Hormiga_Evadir::Execute(Hormiga* hormiga){
		
	Tablero* t = hormiga->GetTablero();

	//si vemos un matador lo evadimos	
	Matador *m = t->GetClosestMatador(hormiga);
	if (m != NULL){
		float dist = Utils::GetVecDistance(m->GetPosition(), hormiga->GetPosition());
		if (dist < DISTANCIAVISTA)
			hormiga->Evade(m);
		else
			hormiga->GetFSM()->ChangeState(State_Hormiga_Deambular::Instance());
	}
	else
	{
		hormiga->GetFSM()->ChangeState(State_Hormiga_Deambular::Instance());
	}

	hormiga->Move();

}

void State_Hormiga_Evadir::Exit(Hormiga* hormiga){


}

char* State_Hormiga_Evadir::GetStateName(){
	return "Evadir";
}


State_Hormiga_BuscarComida*  State_Hormiga_BuscarComida::Instance(){
	static State_Hormiga_BuscarComida instance;
	return &instance;
}

/////////////////////////////////////////////////////////////////////////////
//Buscar Comida
/////////////////////////////////////////////////////////////////////////////

void State_Hormiga_BuscarComida::Enter(Hormiga* hormiga){
}

void State_Hormiga_BuscarComida::Execute(Hormiga* hormiga){

	Tablero* t = hormiga->GetTablero();
	
	bool isEvadir = false;
	
	//si vemos un matador lo evadimos
	Matador *m = t->GetClosestMatador(hormiga);
	if (m != NULL){
		float dist = Utils::GetVecDistance(m->GetPosition(), hormiga->GetPosition());
		if (dist < DISTANCIAVISTA)
		{
			hormiga->GetFSM()->ChangeState(State_Hormiga_Evadir::Instance());
			isEvadir = true;
		}
	}

	if (!isEvadir)
	{
		//vemos si hay alimento cerca
		Comida *c = t->GetNearestVisibleFood(hormiga);
		//guardamos el objetivo 
		if (c != NULL)
			hormiga->SetTarget(c);
		else
			hormiga->GetFSM()->ChangeState(State_Hormiga_Deambular::Instance());

		if (hormiga->GetTarget() != NULL)
		{
			//si estamos muy cerca lo comemos
			float dist = Utils::GetVecDistance(hormiga->GetPosition(), hormiga->GetTarget()->GetPosition());
			if (dist < EATDIST){
				hormiga->GetTablero()->EatComida(hormiga->GetTarget());
				hormiga->GetFSM()->ChangeState(State_Hormiga_Deambular::Instance());
			}
			else
			{
				//Ajusta la direccion
				hormiga->Chase();
			}
		}
	}

	hormiga->Move();

	

}

void State_Hormiga_BuscarComida::Exit(Hormiga* hormiga){


}

char* State_Hormiga_BuscarComida::GetStateName(){
	return "Buscar Comida";
}