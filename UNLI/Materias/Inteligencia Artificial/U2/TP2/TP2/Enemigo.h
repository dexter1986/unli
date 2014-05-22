#pragma once

#include <string>
#include "Vehiculo.h"

class Enemigo : public Vehiculo
{
	private:
		//A quien cazara
		Vehiculo *m_pPresa;

	public:
		friend class EstadoDeambular;
		friend class EstadoPerseguir;

		Enemigo(Vehiculo* pPresa, const b2BodyDef& CuerpoDef, const b2FixtureDef& AdornoDef, float escala, sf::Texture* pTextura);

		std::string GetNombreEstadoActual();
};