#include "EstadoPerseguir.h"
#include "EstadoDeambular.h"
#include "Enemigo.h"

#include <iostream>

#include "MiGame.h"

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

EstadoPerseguir::EstadoPerseguir() : Estado("EstadoPerseguir")
{}

EstadoPerseguir::EstadoPerseguir(const EstadoPerseguir& cpy)
{
	this->m_Nombre = cpy.m_Nombre;
}

EstadoPerseguir& EstadoPerseguir::operator=(const EstadoPerseguir& cpy)
{
	this->m_Nombre = cpy.m_Nombre;
	return *this;
}

EstadoPerseguir::~EstadoPerseguir()
{}

//-------------------------------------------------------------//
//-----------------		Metodos		---------------------------//
//-------------------------------------------------------------//


EstadoPerseguir* EstadoPerseguir::Singleton()
{
	static EstadoPerseguir instancia;
	return &instancia;
}

void EstadoPerseguir::Entrar(EntidadBase* pEntidad)
{
	Enemigo* pEnemigo = dynamic_cast<Enemigo*>(pEntidad);
	std::cout<<"Entro a EstadoPerseguir"<<std::endl;

	pEnemigo->GetSteeringBehaviors().InterceptarOn();
	pEnemigo->GetSteeringBehaviors().m_pPresa = pEnemigo->m_pPresa;

}

void EstadoPerseguir::Ejecutar(EntidadBase* pEntidad)
{
	Enemigo* pEnemigo = dynamic_cast<Enemigo*>(pEntidad);

	FSM& persecutorFSM = pEntidad->GetFSM();

	sf::Vector2f dist = pEnemigo->GetPosicion() - pEnemigo->m_pPresa->GetPosicion();
	if( sqrt(dist.x*dist.x+dist.y*dist.y) > 200)
	{
		persecutorFSM.CambiarEstado(EstadoDeambular::Singleton());
		return;
	}
}

void EstadoPerseguir::Salir(EntidadBase* pEntidad)
{
	Enemigo* pEnemigo = dynamic_cast<Enemigo*>(pEntidad);

	pEnemigo->GetSteeringBehaviors().InterceptarOff();
}