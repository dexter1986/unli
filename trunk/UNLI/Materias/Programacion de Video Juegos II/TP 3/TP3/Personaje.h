#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "SpriteBase.h"

class Personaje :
	public SpriteBase
{
private:
	static const int CLIM_VEL = 20;
	static const int CRAW_VEL = 20;
	static const int SNEAK_VEL = 25;
	static const int SLIDE_VEL = 20;
	float SHOOT_TIME;
	static const int VEL_MISILES=200;

	enum Estado{
		NORMAL,
		TURN,
		TURN_DUCK,
		WALK,		
		RUN,
		JUMP_UP,
		JUMP_DOWN,
		JUMP_AND_RUN_UP,
		JUMP_AND_RUN_DOWN,
		CRAW_AND_WALK,		
		CRAW,
		SNEAK,
		SNEAK_AND_RUN,
		CLIM,
		CLIM_UP,
		CLIM_DOWN,
		SLIDE,		
		SPRINT,
		KICK,
		THROW,
		DUCK,		
		ATTACK1,
		ATTACK2,
		ARM1,
		ARM2,
		RUN_AND_ARM1,
		RUN_AND_ARM2,		
		DUCK_AND_ARM1,
		DUCK_AND_ARM2,
		NORMAL_AND_ARM1,
		NORMAL_AND_ARM2,
		JUMP
	};

	float delayToBreak;
	bool IsDisparoStart;
	bool IsTirarStart;
	bool IsJumpStart;
	bool IsClim_TO_JUMP;
	bool DelayToBreak(bool reset=false,float value=0.1f);	

protected:			
	// inicializa las animaciones, es llamado en el constructor
	void InicializarAnimaciones();	
	// algunas acciones
	void Saltar();	
	bool VerifyFall();
	bool VerifyFallAndRun();	
	void Internal_Mover_y_Animar();
	void DisparoArma1();
	void ArrojarPiedra();		
	void Slide();
public:
	Personaje(void);
	~Personaje(void);		
};

#endif
