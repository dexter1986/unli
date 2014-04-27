#include "MatadorStates.h"
#include "Tablero.h"
#include "utils.h"

State_Matador_Deambular*  State_Matador_Deambular::Instance(){
		static State_Matador_Deambular instance;
		return &instance;
}

/////////////////////////////////////////////////////////////////////////////
//Deambular
/////////////////////////////////////////////////////////////////////////////

void State_Matador_Deambular::Enter(Matador* matador){


}

void State_Matador_Deambular::Execute(Matador* matador){

	//Calculamos si hay que cambiar de estado
	Tablero* t=matador->GetTablero();

	//vemos si hay una hormiga cerca 
	Hormiga* g= t->GetClosestHormiga(matador);
	if(g!=NULL){
		float dist = Utils::GetVecDistance(g->GetPosition(), matador->GetPosition());
		if(dist< DISTANCIAVISTA )//cambiamos al estado perseguir
			matador->GetFSM()->ChangeState(State_Matador_Perseguir::Instance());
	}
	
	//calculamos si vamos a cambiar de dirección
	if (Utils::GetRandomIntValue(0, 100) == 0){
		matador->ChangeDirection();
	}
	
	matador->Move();


}

void State_Matador_Deambular::Exit(Matador* matador){


}

char* State_Matador_Deambular::GetStateName(){
	return "Deambular";
}


State_Matador_Perseguir*  State_Matador_Perseguir::Instance(){
		static State_Matador_Perseguir instance;
		return &instance;
}

/////////////////////////////////////////////////////////////////////////////
//Perseguir
/////////////////////////////////////////////////////////////////////////////

void State_Matador_Perseguir::Enter(Matador* matador){



}

void State_Matador_Perseguir::Execute(Matador* matador)
{
	//buscamos la hormiga mas cercana
	Tablero* t=matador->GetTablero();

	Hormiga* g= t->GetClosestHormiga(matador);
	//guardamos el objetivo en el objeto matador
	if(g!=NULL)
		matador->SetTarget(g);
	else
		matador->GetFSM()->ChangeState(State_Matador_Deambular::Instance());
	
	if( matador->GetTarget() != NULL)
	{
		//si estamos muy cerca lo comemos
		float dist = Utils::GetVecDistance(matador->GetPosition(), matador->GetTarget()->GetPosition());
		if (dist<EATDIST){
			matador->GetTablero()->KillHormiga(matador->GetTarget());
			matador->GetFSM()->ChangeState(State_Matador_Deambular::Instance());
		}
		//lo pierde de vista
		if (dist>DISTANCIAVISTA){
			matador->GetFSM()->ChangeState(State_Matador_Deambular::Instance());
		}

		//Update chase direction
		matador->Chase();
	}
	//move
	matador->Move();
}

void State_Matador_Perseguir::Exit(Matador* matador){


}

char* State_Matador_Perseguir::GetStateName(){
	return "Perseguir";
}
