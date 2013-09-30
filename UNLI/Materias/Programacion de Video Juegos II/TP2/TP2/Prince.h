#ifndef PRINCE_H
#define PRINCE_H

#include "SpriteBase.h"

class Prince :
	public SpriteBase
{
private:
	static const int CLIM_VEL = 10;
	enum Estado{
		NORMAL,
		TURN,		
		WALK,		
		RUN,
		JUMP_UP,
		JUMP_DOWN,
		JUMP_AND_RUN_UP,
		JUMP_AND_RUN_DOWN,
		CRAW_AND_WALK,		
		CRAW,
		SNEAK,
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
	bool IsJumpStart;
	bool DelayToBreak(bool reset=false,float value=0.1f);

protected:			
	// inicializa las animaciones, es llamado en el constructor
	void InicializarAnimaciones();	
	// algunas acciones
	void Saltar();	
	bool ColisionaConSuelo();	
	void Internal_Mover_y_Animar();
	void DisparoArma1();
	bool IsColisionPared();
public:
	Prince(void);
	~Prince(void);		
};

#endif
