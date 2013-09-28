#ifndef SPRITEBASE_H
#define SPRITEBASE_H

#include "AnimatedBase.h"

// una estructura simple para pasarle los controles a megaman
struct Joystick{
	bool up, down, left, right, a, b;
};

class SpriteBase :
	public Sprite
{
protected:
	
	enum Direccion
	{
		UP,
		LEFT,
		RIGHT,
		DOWN
	};

	float v0;		// velocidad inicial al comenzar el salto 
	float gravity;	// gravedad
	float delay;
	int currentState;
	Vector2f velocidad;
	Vector2f posicion;
	Vector2f posicion_inicial;
	float dt;
	Joystick joystick;
	Direccion direccion;// si apunta a la der o izq (flip horizontal de la textura)

	AnimatedBase *animaciones;
	
	// inicializa las animaciones, es llamado en el constructor
	bool IsAnimationEnded();
	void AnimationStop();
	int AnimationCurrentFrame();
	virtual void InicializarAnimaciones()=0;
	virtual void Internal_Mover_y_Animar()=0;
	// cambia el estado y hace algunas operaciones necesarias
	void CambiarEstado(int nuevoEstado, bool continueFromCurrent=false);	
	void AnimationReverse(bool reverse);
	bool DelayTransition(bool reset=false);
public:
	void Inicializar();
	SpriteBase(int cant_estados,const string &filename);
	void Mover_y_Animar(Joystick j, float dt);	
	virtual ~SpriteBase(void);
};

#endif

