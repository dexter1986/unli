#include "EstadoDeambular.h"
#include "EstadoPerseguir.h"
#include "Enemigo.h"

#include <iostream>

#include "MiGame.h"

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

EstadoDeambular::EstadoDeambular() : Estado("EstadoDeambular")
{}

EstadoDeambular::EstadoDeambular(const EstadoDeambular& cpy)
{
	this->m_Nombre = cpy.m_Nombre;
}

EstadoDeambular& EstadoDeambular::operator=(const EstadoDeambular& cpy)
{
	this->m_Nombre = cpy.m_Nombre;
	return *this;
}

EstadoDeambular::~EstadoDeambular()
{}

//-------------------------------------------------------------//
//-----------------		Metodos		---------------------------//
//-------------------------------------------------------------//


EstadoDeambular* EstadoDeambular::Singleton()
{
	static EstadoDeambular instancia;
	return &instancia;
}

void EstadoDeambular::Entrar(EntidadBase* pEntidad)
{
	Enemigo* pEnemigo = dynamic_cast<Enemigo*>(pEntidad);
	std::cout<<"Entro a EstadoDeambular"<<std::endl;	
}

void EstadoDeambular::Ejecutar(EntidadBase* pEntidad)
{
	Enemigo* pEnemigo = dynamic_cast<Enemigo*>(pEntidad);
	FSM& vahiculoFSM = pEntidad->GetFSM();

	sf::Vector2f dist = pEnemigo->GetPosicion() - pEnemigo->m_pPresa->GetPosicion();
	if( sqrt(dist.x*dist.x+dist.y*dist.y) < 400 )//Si el enemigo esta muy cerca cambia de estado para atacar
	{
		vahiculoFSM.CambiarEstado(EstadoPerseguir::Singleton());
		return;
	}
}

void EstadoDeambular::Salir(EntidadBase* pEntidad)
{
	Enemigo* pEnemigo = dynamic_cast<Enemigo*>(pEntidad);
}