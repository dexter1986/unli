#pragma once
#include "SpriteBase.h"

class GameEngine;

class Personaje : public SpriteBase
{
private:
	static const int CLIM_VEL = 20;
	static const int CRAW_VEL = 20;
	static const int SNEAK_VEL = 25;
	static const int SLIDE_VEL = 20;
	

	float SHOOT_TIME;
	static const int VEL_MISILES=400;

	enum Estado{
		NORMAL,
		NORMAL_J,
		TURN,
		TURN_DUCK,
		DUCK,			
		RUN,		
		JUMP_UP,
		JUMP_DOWN,
		JUMP_AND_RUN_UP,
		JUMP_AND_RUN_DOWN,
		CRAW_AND_WALK,				
		SNEAK,
		SNEAK_AND_RUN,
		CLIM,
		CLIM_UP,
		CLIM_DOWN,
		SLIDE,	
		RUN_AND_ARM1,			
		DUCK_AND_ARM1,		
		NORMAL_AND_ARM1		
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
	void Internal_Mover_y_Animar2();
	void DisparoArma1();
	void ArrojarPiedra();		
	void Slide();
public:
	void ResetState();
	Personaje(GameEngine *e);
	~Personaje(void);		
};
