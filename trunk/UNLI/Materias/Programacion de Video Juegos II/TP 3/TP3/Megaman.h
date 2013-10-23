#ifndef MEGAMAN_H
#define MEGAMAN_H

#include "Megaman.h"
#include "Animation.h"
#include "SpriteSheetManager.h"
#include "Disparos.h"
#include "SpriteBase.h"

// una estructura simple para pasarle los controles a megaman
//struct Joystick{
//	bool up, down, left, right, a, b;
//};


class Megaman: public Sprite{
	private:
	enum Estado{
		PARADO,
		CORRIENDO,
		DISPARANDO,
		SALTANDO,
		DISPARANDO_Y_CORRIENDO,
		SALTANDO_Y_DISPARANDO,
		SALTANDO_Y_MOVIENDOSE,
		SALTANDO_MOVIENDOSE_Y_DISPARANDO
	};
	Estado estado;				// el estado actual
	int direccion;				// si apunta a la der o izq (flip horizontal de la textura)
	Animation animaciones[8];	// animaciones para cada estado
	SpriteSheetManager im;		// nuestro manejador de la spritesheet
	ManejadorDisparos *disparos;// clase que se encargara de mover/dibujar los disparos
	
	float vy;					// velocidad actual en y (salto y caida)
	float shootTime;			// tiempo que transcurrio desde el ultimo disparo
	float y0;					// posicion desde donde comenzo el ultimo salto
	
	// inicializa las animaciones, es llamado en el constructor
	void InicializarAnimaciones();
	
	// cambia el estado y hace algunas operaciones necesarias
	void CambiarEstado(Estado nuevoEstado, bool continueFromCurrent=false);
	
	// algunas acciones
	void Saltar();
	void Disparar(float x, float y);
	
	// funciones que determinan eventos de entrada
	bool SecuenciaDisparoFinalizada();
	bool ColisionaConSuelo();
	
	public:
	Megaman(ManejadorDisparos *d);
	void Mover_y_Animar(Joystick j, float dt);
};

#endif

