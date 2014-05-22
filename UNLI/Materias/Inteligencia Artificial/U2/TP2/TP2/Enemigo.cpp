#include "Enemigo.h"
#include "EstadoDeambular.h"

//-------------------------------------------------------------//
//-------------	Constructor/Destructor	-----------------------//
//-------------------------------------------------------------//

Enemigo::Enemigo(Vehiculo* pPresa, const b2BodyDef& CuerpoDef, const b2FixtureDef& AdornoDef, float escala, sf::Texture* pTextura) :
											Vehiculo(CuerpoDef, AdornoDef, escala, pTextura),
											m_pPresa(pPresa)
{
	//Empezamos la FSM en el EstadoQuieto
	m_MaquinaDeEstadoFinito.CambiarEstado(EstadoDeambular::Singleton());
}

//-------------------------------------------------------------//
//-----------------		Metodos		---------------------------//
//-------------------------------------------------------------//

std::string Enemigo::GetNombreEstadoActual()
{
	return m_MaquinaDeEstadoFinito.GetNombreEstadoActual();
}