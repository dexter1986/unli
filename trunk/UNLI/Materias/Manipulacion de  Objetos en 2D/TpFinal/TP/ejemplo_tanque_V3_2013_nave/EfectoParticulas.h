#ifndef FX_H
#define FX_H

#include <cmath>
#include <sstream>
#include <iostream>
#include <fstream>
#include <list>

#include <GL\glut.h>
#include "Particula.h"
#include "Helper.h"

using namespace std;

namespace EfectoParticulasConfig
{
	enum EfectoParticulasTypeFX
	{
		Propulsion,
		HuellaVehiculo,
		Incendio
	};
}

// Clase que representa un efecto de particulas
// Con el que se puede simular de forma simple efectos de humo, fuego, chispas, etc
class EfectoParticulas
{
	public:
		
		EfectoParticulasConfig::EfectoParticulasTypeFX tipoEfecto;

		// Contructor del efecto de particulas.
		// Se le deben especificar las propiedades basicas del efecto
		EfectoParticulas(float x, float y,float z,float _aceleracionY = 0.0f, float _aceleracionX = 0.0f,
		int _tamano = 4, int _cantidad = 150, int _vida = 20, float _velocidad = 2.0f,
		int _amplitud = 90, int _direccion = 45);
		
		// Actualiza las posiciones de las particulas lanzadas del efecto y lanza nuevas particulas si es necesario
		void Actualizar();
		
		// Dibuja las particulas del efecto y el punto de origen del efecto
		void Dibujar();
		
		// Cambia el estado de "encendido" del efecto
		void ToggleActivo();
		
		// Obtiene el estado de "encendido" del efecto
		bool GetActivo();
		
		// Establece la posicion del efecto de particulas
		void SetPosicion(float x, float y);
		
		// Obtiene la aceleracion de gravedad de las particulas
		float GetAceleracionY();
		
		// Establece la aceleracion de gravedad de las particulas
		void SetAceleracionY(float _aceleracionY);
		
		// Obtiene el tamano de las particulas
		int GetTamano();
		
		// Establece el tamano de las particulas
		void SetTamano(int _tamano);
		
		// Obtiene la cantidad de particulas del efecto
		int GetCantidad();
		
		// Establece la cantidad de particulas del efecto
		void SetCantidad(int _cantidad);
		
		// Obtiene la cantidad de vida maxima de las particulas nuevas
		int GetVida();
		
		// Establece la cantidad de vida maxima de las particulas nuevas
		void SetVida(int _vida);
		
		// Obtiene la velocidad a la que salen las particulas
		float GetVelocidad();
		
		// Establece la velocidad a la que salen las particulas
		void SetVelocidad(float _velocidad);
		
		// Obtiene el angulo de apertura en el que salen particulas desde
		// la direccion de lanzamiento
		int GetAmplitud();
		
		// Establece el angulo de apertura en el que salen particulas desde
		// la direccion de lanzamiento
		void SetAmplitud(int _amplitud);
		
		// Obtiene el angulo de lanzamiento de nuevas particulas
		int GetDireccion();
		
		// Establece el angulo de lanzamiento de nuevas particulas
		void SetDireccion(int _direccion);
		
		// Cambia el paso temporal con el que se actualizan las particulas
		void SetDeltaTiempo(float _dt);
		
		// Establece el color de las particulas
		// Por defecto estas son de color azul
		void SetColor(float _r, float _g, float _b);
	
	private:
		// Arreglo de las particulas del efecto
		Particula* particulas;
		
		// Posicion X del efecto
		float posicionX;
		
		// Posicion Y del efecto
		float posicionY;

		float posicionZ;
		
		// Aceleracion en el eje Y
		float aceleracionY;

		float aceleracionX;
		
		// Tamano de las particulas
		int tamano;
		
		// Cantidad de particulas
		int cantidad;
		
		// Tiempo de vida de las particulas
		int vida;
		
		// Velocidad de las particulas
		float velocidad;
		
		// Amplitud de salida de las particulas
		// En grados
		int amplitud;
		
		// Direccion de salida de las particulas
		// En grados
		int direccion;
		
		// Paso de tiempo de la simulacion
		float dt;
		
		// Componente rojo del color de las particulas
		float r; 
		
		// Componente verde del color de las particulas
		float g; 
		
		// Componente azul del color de las particulas
		float b;
		
		// Si el efecto esta activo actualmente
		bool activo;
};

#endif