#pragma once

#include "Estado.h"

class EstadoDeambular : public Estado
{
	private:
		EstadoDeambular();

		EstadoDeambular(const EstadoDeambular& cpy);

		EstadoDeambular& operator=(const EstadoDeambular& cpy);
		
	public:
		~EstadoDeambular();

		//Nos devuelve la unica instancia de la clase
		static EstadoDeambular* Singleton();

		virtual void Entrar(EntidadBase* pEntidad);

		virtual void Ejecutar(EntidadBase* pEntidad);

		virtual void Salir(EntidadBase* pEntidad);
};