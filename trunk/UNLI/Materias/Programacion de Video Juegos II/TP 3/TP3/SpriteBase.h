#ifndef SPRITEBASE_H
#define SPRITEBASE_H

#include <math.h>
#include "AnimatedBase.h"
#include "Nivel.h"
#include "Disparos.h"

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
	float ajustaColision_y,ajustaColision_x; // ajuste de colision
	int currentState;
	Vector2f velocidad;
	Vector2f posicion;
	Vector2f posicion_inicial;
	Vector2f scale;
	float dt;
	Joystick joystick;
	Direccion direccion;// si apunta a la der o izq (flip horizontal de la textura)

	bool isNPC;
	bool isHitWall;

	int vidas;

	AnimatedBase *animaciones;
	FloatRect aabb;
	
	Nivel *nivel;
	
	ManejadorDisparos *disparos;
	float shootTime;

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
	void CalculateAABB();
	void SetOffsetAABB(Vector2f &offset);
	bool ColisionaPared();
	bool ColisionaTecho();
	bool ColisionaSuelo();
	void AjustaColisionX();
	void AjustaColisionY();	
	bool SecuenciaDisparoFinalizada();
	void Disparar(float x, float y,float shoot_time,float velmisiles);
	void Disparar(float shootTime,float vel_misiles);
	virtual void AiNpc();
public:	
	int GetDireccionX();
	FloatRect &GetAABB();
	virtual void Inicializar(ManejadorDisparos *d,Nivel *n);
	SpriteBase(int cant_estados,const string &filename,float scale_x=0,float scale_y=0,bool NPC=false);
	void Mover_y_Animar(Joystick j, float dt);	
	void Mover_y_Animar_NPC(float dt);	
	virtual ~SpriteBase(void);
};

#endif

