#pragma once

#include "Estado.h"

class EstadoPerseguir : public Estado
{
	private:
		EstadoPerseguir();

		EstadoPerseguir(const EstadoPerseguir& cpy);

		EstadoPerseguir& operator=(const EstadoPerseguir& cpy);
		
	public:
		virtual ~EstadoPerseguir();

		//Nos devuelve la unica instancia de la clase
		static EstadoPerseguir* Singleton();

		virtual void Entrar(EntidadBase* pEntidad);

		virtual void Ejecutar(EntidadBase* pEntidad);

		virtual void Salir(EntidadBase* pEntidad);
};