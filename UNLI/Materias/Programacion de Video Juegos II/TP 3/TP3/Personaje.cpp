#include "Personaje.h"

Personaje::Personaje(void):SpriteBase(30,"../data/personaje.png",0.5,0.5)
{
	currentState = Estado::NORMAL;	
	direccion = Direccion::RIGHT;
	velocidad.x = 60.0f;
	delayToBreak = 0;
	IsJumpStart = false;
	IsTirarStart = false;
	IsClim_TO_JUMP = false;
	SHOOT_TIME = 0.5f;
	shootTime=SHOOT_TIME;
}

Personaje::~Personaje(void)
{
}

void Personaje::InicializarAnimaciones()
{
	int w;
	int h;
	int xo;
	int yo;
	float offset_x=0;
	float offset_y=0;
	float framelengh = 0.1;
	
	xo = 222;
	yo = 368;
	w = 22;
	h = 57;
	animaciones[Estado::NORMAL].SetAABB(FloatRect(2,2,10,26));
	animaciones[Estado::NORMAL].SetLoop(false);
	animaciones[Estado::NORMAL].AddFrame(145,285,w,h,framelengh);

	animaciones[Estado::TURN].SetAABB(FloatRect(2,2,10,26));
	animaciones[Estado::TURN].SetLoop(false);
	animaciones[Estado::TURN].AddFrame(145,285,w,h,0.2);

		
	xo = 272;
	yo = 285;	
	w = 36;
	h = 57;
	animaciones[Estado::NORMAL_AND_ARM1].SetAABB(FloatRect(2,2,10,26));
	animaciones[Estado::NORMAL_AND_ARM1].SetLoop(false);
	animaciones[Estado::NORMAL_AND_ARM1].AddFrame(xo,yo,w,h,framelengh,0.0,0.0,14.0);

	xo = 14;
	yo = 447;
	w = 31;
	h = 55;
	for(int i=0;i<6;i++)
	{
		animaciones[Estado::RUN].AddFrame(xo+w*i,yo,w,h,framelengh,0.0,-2.0,10.0,-2.0);
	}

	animaciones[Estado::RUN].SetAABB(FloatRect(2,2,10,26));

	xo = 209;
	yo = 448;
	w = 42;
	h = 55;
	
	animaciones[Estado::RUN_AND_ARM1].SetAABB(FloatRect(2,2,10,26));
	for(int i=0;i<6;i++)
	{
		animaciones[Estado::RUN_AND_ARM1].AddFrame(xo+w*i,yo,w,h,framelengh,0.0,-2.0,21.0,-2.0);
	}


	xo = 18;
	yo = 301;
	w = 28;
	h = 41;	
	animaciones[Estado::DUCK].SetAABB(FloatRect(2,10,10,26));
	animaciones[Estado::DUCK].SetLoop(false);
	animaciones[Estado::DUCK].AddFrame(xo,yo,w,h,framelengh,0.0,-16.0,0.0,-16.0);

	animaciones[Estado::TURN_DUCK].SetAABB(FloatRect(2,10,10,26));
	animaciones[Estado::TURN_DUCK].SetLoop(false);
	animaciones[Estado::TURN_DUCK].AddFrame(xo,yo,w,h,0.2,0.0,-16.0,0.0,-16.0);

	xo = 58;
	yo = 298;
	w = 31;
	h = 44;		
	animaciones[Estado::DUCK_AND_ARM1].SetAABB(FloatRect(2,10,10,26));
	animaciones[Estado::DUCK_AND_ARM1].SetLoop(false);
	animaciones[Estado::DUCK_AND_ARM1].AddFrame(xo,yo,w,h,framelengh,1.6,-13.0,0.0,-13.0);
	
	xo = 16;
	yo = 197;
	w = 31;
	h = 62;			
	animaciones[Estado::JUMP_UP].SetAABB(FloatRect(2,2,10,26));
	animaciones[Estado::JUMP_UP].SetLoop(false);
	animaciones[Estado::JUMP_UP].AddFrame(xo,yo,w,h,0.15,0,0,5);
	for(int i=1;i<3;i++)
	{
		animaciones[Estado::JUMP_UP].AddFrame(xo+w*i,yo,w,h,framelengh,0,0,5);
	}

	animaciones[Estado::JUMP_DOWN].SetAABB(FloatRect(2,2,10,26));
	animaciones[Estado::JUMP_DOWN].SetLoop(false);	
	animaciones[Estado::JUMP_DOWN].AddFrame(xo+w*3,yo,w,h,framelengh,0,0,5);
	
	xo = 16;
	yo = 197;
	w = 31;
	h = 62;			
	animaciones[Estado::JUMP_AND_RUN_UP].SetAABB(FloatRect(2,2,10,26));
	animaciones[Estado::JUMP_AND_RUN_UP].SetLoop(false);
	animaciones[Estado::JUMP_AND_RUN_UP].AddFrame(xo,yo,w,h,0.15,0,0,5);
	for(int i=1;i<3;i++)
	{
		animaciones[Estado::JUMP_AND_RUN_UP].AddFrame(xo+w*i,yo,w,h,framelengh,0,0,5);
	}

	animaciones[Estado::JUMP_AND_RUN_DOWN].SetAABB(FloatRect(2,2,10,26));
	animaciones[Estado::JUMP_AND_RUN_DOWN].SetLoop(false);	
	animaciones[Estado::JUMP_AND_RUN_DOWN].AddFrame(xo+w*3,yo,w,h,framelengh,0,0,5);

	xo = 13;
	yo = 599;
	w = 28;
	h = 57;		
	animaciones[Estado::CLIM].SetAABB(FloatRect(2,2,10,10));
	animaciones[Estado::CLIM].SetLoop(false);
	animaciones[Estado::CLIM].AddFrame(xo,yo,w,h,framelengh);

	animaciones[Estado::SLIDE].SetAABB(FloatRect(2,2,10,26));
	animaciones[Estado::SLIDE].SetLoop(false);
	animaciones[Estado::SLIDE].AddFrame(xo,yo,w,h,framelengh);

	for(int i=0;i<6;i++)
	{
		animaciones[Estado::CLIM_UP].AddFrame(xo+w*i,yo,w,h,framelengh);
	}
	animaciones[Estado::CLIM_UP].SetAABB(FloatRect(2,2,10,10));
	
	for(int i=5;i>0;i--)
	{
		animaciones[Estado::CLIM_DOWN].AddFrame(xo+w*i,yo,w,h,framelengh);
	}
		
	animaciones[Estado::CLIM_DOWN].SetAABB(FloatRect(2,2,10,10));

	xo = 15;
	yo = 157;
	w = 50;
	h = 31;
	for(int i=0;i<6;i++)
	{
		//animaciones[Estado::CRAW_AND_WALK].AddFrame(xo+w*i,yo,w,h,framelengh,0,-26.0f,20.0f,-26.0f);		
		animaciones[Estado::CRAW_AND_WALK].AddFrame(xo+w*i,yo,w,h,framelengh,20.0f,-26.0f, 5.0f,-26.0f);		
	}
	animaciones[Estado::CRAW_AND_WALK].SetAABB(FloatRect(2,12,10,26));

	animaciones[Estado::CRAW].SetAABB(FloatRect(2,12,10,26));
	animaciones[Estado::CRAW].SetLoop(false);
	//animaciones[Estado::CRAW].AddFrame(xo,yo,w,h,framelengh,10,-26.0f,20.0f,-26.0f);
	animaciones[Estado::CRAW].AddFrame(xo,yo,w,h,framelengh,20,-26.0f,5.0f,-26.0f);

	xo = 147;
	yo = 217;
	w = 29;
	h = 49;
	for(int i=0;i<6;i++)
	{
		animaciones[Estado::SNEAK_AND_RUN].AddFrame(xo+w*i,yo,w,h,framelengh,0,-8.3f,0,-8.3f);
	}	

	animaciones[Estado::SNEAK_AND_RUN].SetAABB(FloatRect(2,2,10,26));

	animaciones[Estado::SNEAK].SetAABB(FloatRect(2,2,10,26));
	animaciones[Estado::SNEAK].SetLoop(false);
	animaciones[Estado::SNEAK].AddFrame(xo,yo,w,h,framelengh,0,-8.3f,0,-8.3f);
	//Add Kick
	//joytick.b when is Normal and Is near a door
	//Add Throw
	//joytick.b when is Normal (throw Stone)
	xo = 13;
	yo = 818;
	w = 53;
	h = 57;
	for(int i=0;i<6;i++)
	{
		animaciones[Estado::THROW].AddFrame(xo+w*i,yo,w,h,framelengh,5.0f,0,22.0f);
	}
	animaciones[Estado::THROW].SetAABB(FloatRect(2,2,10,26));
	animaciones[Estado::THROW].SetLoop(false);

}

void Personaje::Internal_Mover_y_Animar()
{
	float distAjuste = 0;
	switch(currentState)
	{
		case TURN:
			if(IsAnimationEnded())
			{
				CambiarEstado(Estado::NORMAL);				
			}
			break;		
		case TURN_DUCK:
			if(IsAnimationEnded())
			{
				CambiarEstado(Estado::DUCK);				
			}
			break;
		case NORMAL:
			if(joystick.right)
			{	
				if(direccion != Direccion::RIGHT)
				{
					direccion = Direccion::RIGHT;
					CambiarEstado(Estado::TURN);
				}
				else
				{
					if(!ColisionaPared())
					{
						CambiarEstado(Estado::RUN);						
					}
					else
					{
						AjustaColisionX();						
					}
				}
			}
			else if(joystick.left)
			{
				if(direccion != Direccion::LEFT)
				{
					direccion = Direccion::LEFT;
					CambiarEstado(Estado::TURN);
				}
				else
				{
					if(!ColisionaPared())
					{
						CambiarEstado(Estado::RUN);								
					}
					else
					{
						AjustaColisionX();						
					}
				}
			}			
			
			if(joystick.down)
			{	
				CambiarEstado(Estado::DUCK);				
			}			
			
			if(joystick.a)
			{	
				CambiarEstado(Estado::NORMAL_AND_ARM1);				
			}
			
			/*if(!IsTirarStart && joystick.b)
			{	
				CambiarEstado(Estado::THROW);				
			}*/
			
			
			VerifyFall();
			

			if(joystick.up)
			{
				CambiarEstado(Estado::JUMP_UP);
				Saltar();				
			}
			
			/*
			 if(joystick.b && joystick.up)
			{
				CambiarEstado(Estado::CLIM_UP);				
			}*/
			break;
		case NORMAL_AND_ARM1:
			if(joystick.right)
			{	
				if(direccion != Direccion::RIGHT)
				{
					direccion = Direccion::RIGHT;
					CambiarEstado(Estado::TURN);
				}
				else
				{
					if(!ColisionaPared())
					{
						CambiarEstado(Estado::RUN_AND_ARM1);						
					}
					else
					{	
						AjustaColisionX();						
					}
				}
			}
			else if(joystick.left)
			{	
				if(direccion != Direccion::LEFT)
				{
					direccion = Direccion::LEFT;
					CambiarEstado(Estado::TURN);
				}
				else
				{	
					if(!ColisionaPared())
					{
						CambiarEstado(Estado::RUN_AND_ARM1);								
					}
					else
					{	
						AjustaColisionX();						
					}
				}
			}
			
			VerifyFall();

			if(!joystick.a)
			{
				CambiarEstado(Estado::NORMAL);
				break;
			}
			if(joystick.down)
			{
				CambiarEstado(Estado::DUCK_AND_ARM1);				
			}
			
			DisparoArma1();
			break;
		case THROW:			
			if(IsAnimationEnded())
			{
				ArrojarPiedra();
				CambiarEstado(Estado::NORMAL);
			}
			break;		
		case CRAW:
			if(!joystick.down)
			{
				CambiarEstado(Estado::NORMAL);
			}

			if(joystick.left && direccion == Direccion::LEFT || joystick.right && direccion == Direccion::RIGHT)
			{	
				if(!ColisionaPared())
				{
					CambiarEstado(Estado::CRAW_AND_WALK);							
				}
				else
				{
					if(direccion == Direccion::RIGHT)
					{
						Move(ajustaColision_x,0);
					}
					else
					{	
						AjustaColisionX();
					}
				}
			}
			else if(joystick.left && direccion != Direccion::LEFT || joystick.right && direccion != Direccion::LEFT)
			{
				CambiarEstado(Estado::TURN_DUCK);				
			}
			break;
		case CRAW_AND_WALK:		
			if(ColisionaPared())
			{	
				CambiarEstado(Estado::DUCK);
				if(direccion == Direccion::RIGHT)
				{
					Move(ajustaColision_x,0);
				}
				else
				{						
					AjustaColisionX();
				}
			}
			if(!joystick.down) 
			{
				CambiarEstado(Estado::NORMAL);
			}

			if(!joystick.left && direccion == Direccion::LEFT || !joystick.right && direccion == Direccion::RIGHT)
			{
				CambiarEstado(Estado::DUCK);
			}
			VerifyFallAndRun();
			break;
		case DUCK_AND_ARM1:
			if(joystick.right)
			{	
				if(direccion != Direccion::RIGHT)
				{
					direccion = Direccion::RIGHT;
					CambiarEstado(Estado::TURN_DUCK);
				}				
			}
			else if(joystick.left)
			{	
				if(direccion != Direccion::LEFT)
				{
					direccion = Direccion::LEFT;
					CambiarEstado(Estado::TURN_DUCK);
				}				
			}
			
			VerifyFall();

			if(!joystick.a)
			{
				CambiarEstado(Estado::DUCK);				
			}
			if(!joystick.down)
			{
				CambiarEstado(Estado::NORMAL_AND_ARM1);			
			}
			
			DisparoArma1();
			break;	
		case DUCK:
			if(joystick.right)
			{	
				if(direccion != Direccion::RIGHT)
				{
					direccion = Direccion::RIGHT;
					CambiarEstado(Estado::TURN_DUCK);
				}
				else
				{
					if(!ColisionaPared())
					{
						CambiarEstado(Estado::CRAW_AND_WALK);						
					}
					else
					{
						AjustaColisionX();
					}
				}				
			}
			else if(joystick.left)
			{
				if(direccion != Direccion::LEFT)
				{
					direccion = Direccion::LEFT;
					CambiarEstado(Estado::TURN_DUCK);
				}
				else
				{
					if(!ColisionaPared())
					{
						CambiarEstado(Estado::CRAW_AND_WALK);						
					}
					else
					{	
						AjustaColisionX();
					}								
				}				
			}
			else if(!joystick.down)
			{
				CambiarEstado(Estado::NORMAL);				
			}
			else if(joystick.a)
			{
				CambiarEstado(Estado::DUCK_AND_ARM1);				
			}
			break;	
		case RUN:			
			if(ColisionaPared())
			{	
				CambiarEstado(Estado::NORMAL);	
				if(direccion == Direccion::RIGHT)
				{
					Move(ajustaColision_x,0);
				}
				else
				{	
					AjustaColisionX();
				}
			}
			else if(!joystick.right && direccion == Direccion::RIGHT || !joystick.left && direccion == Direccion::LEFT)
			{	
				CambiarEstado(Estado::NORMAL);					
			}
			else if(VerifyFallAndRun())
			{
			}
			else
			{
				if(joystick.a)
				{
					CambiarEstado(Estado::RUN_AND_ARM1);				
				}
			}			

			if(joystick.up)
			{
				CambiarEstado(Estado::JUMP_AND_RUN_UP);
				Saltar();				
			}
			else if(joystick.down)
			{
				CambiarEstado(Estado::SNEAK);
			}
			
			break;
		 case SNEAK:

			VerifyFall();

			if(!joystick.down)
			{
				CambiarEstado(Estado::NORMAL);
			}
			else if(joystick.right)
			{	
				CambiarEstado(Estado::SNEAK_AND_RUN);
				direccion = Direccion::RIGHT;
			}
			else if(joystick.left)
			{
				CambiarEstado(Estado::SNEAK_AND_RUN);
				direccion = Direccion::LEFT;			
			}
			break;
		case SNEAK_AND_RUN:
			if(!joystick.right && direccion == Direccion::RIGHT || !joystick.left && direccion == Direccion::LEFT)
			{	
				CambiarEstado(Estado::SNEAK);					
			}

			if(ColisionaPared())
			{		
				CambiarEstado(Estado::NORMAL);
				if(direccion == Direccion::RIGHT)
				{
					AjustaColisionX();
				}
				else
				{
					AjustaColisionX();
				}
			}
			
			VerifyFall();
			
			if(!joystick.down)
			{
				CambiarEstado(Estado::RUN);
			}
			
			if(joystick.right)
			{	
				direccion = Direccion::RIGHT;
			}
			
			if(joystick.left)
			{
				direccion = Direccion::LEFT;			
			}
			
			break;
		case RUN_AND_ARM1:
			if(!joystick.right && direccion == Direccion::RIGHT || !joystick.left && direccion == Direccion::LEFT)
			{
				CambiarEstado(Estado::NORMAL);				
			}
			if(ColisionaPared())
			{
				CambiarEstado(Estado::NORMAL);
				if(direccion == Direccion::RIGHT)
				{
					AjustaColisionX();
				}
				else
				{
					AjustaColisionX();
				}
			}

			VerifyFallAndRun();
			
			if(!joystick.a)
			{
				DelayToBreak(true);
				CambiarEstado(Estado::RUN,true);
			}			
			
			if(joystick.up)
			{
				CambiarEstado(Estado::JUMP_AND_RUN_UP);
				Saltar();			
			}
			DisparoArma1();
			break;	
		case JUMP_UP:
			if(ColisionaTecho())
			{
				CambiarEstado(Estado::JUMP_DOWN);				
				AjustaColisionY();
				velocidad.y=0;				
			}
			if(velocidad.y > 0)
			{	
				CambiarEstado(Estado::JUMP_DOWN);			
			}

			if(joystick.left)
			{
				if(!ColisionaPared())
				{
					direccion = Direccion::LEFT;
					CambiarEstado(JUMP_AND_RUN_DOWN);
				}
				else
				{
					AjustaColisionX();
				}
			}
			if(joystick.right)
			{
				if(!ColisionaPared())
				{
					direccion = Direccion::RIGHT;
					CambiarEstado(JUMP_AND_RUN_DOWN);
				}
				else
				{
					AjustaColisionX();
				}
			}

			//if(!IsJumpStart && joystick.b && ColisionaPared())
			if( joystick.b && ColisionaPared())
			{	
				CambiarEstado(Estado::CLIM);								
			}
			break;
		case JUMP_DOWN:		
			if(ColisionaSuelo())
			{	
				CambiarEstado(Estado::NORMAL);	
				AjustaColisionY();
				velocidad.y = 0;
			}
			//if(!IsJumpStart && joystick.b &&  ColisionaPared())
			if( joystick.b &&  ColisionaPared())
			{	
				CambiarEstado(Estado::CLIM);					
			}			
			break;
		case JUMP_AND_RUN_UP:
			if(ColisionaTecho())
			{
				CambiarEstado(Estado::JUMP_AND_RUN_DOWN);
				AjustaColisionY();
				velocidad.y=0;				
			}
			if(ColisionaPared())
			{
				CambiarEstado(Estado::JUMP_DOWN);
				if(direccion == Direccion::RIGHT)
				{
					AjustaColisionX();
				}
				else
				{
					AjustaColisionX();
				}

				if(joystick.b)
				{	
					CambiarEstado(Estado::CLIM);				
				}
			}
			
			if(velocidad.y > 0)
			{
				CambiarEstado(Estado::JUMP_AND_RUN_DOWN);				
			}
			
			break;
		case JUMP_AND_RUN_DOWN:
			if(ColisionaTecho())
			{
				CambiarEstado(Estado::JUMP_AND_RUN_DOWN);
				AjustaColisionY();
				velocidad.y=0;				
			}
			if(ColisionaSuelo())
			{	
				CambiarEstado(Estado::NORMAL);	
				AjustaColisionY();
				velocidad.y = 0;
			}
			if(ColisionaPared())
			{
				CambiarEstado(Estado::JUMP_DOWN);
				if(direccion == Direccion::RIGHT)
				{
					AjustaColisionX();
				}
				else
				{
					AjustaColisionX();
				}					
				if(joystick.b)
				{		
					CambiarEstado(Estado::CLIM);	
				}
			}
			
			break;
		case CLIM:
			/*if(ColisionaSuelo())
			{	
				CambiarEstado(Estado::NORMAL);	
				AjustaColisionY();
				velocidad.y = 0;
			}*/		
			if(ColisionaTecho())
			{
				AjustaColisionY();	
				CambiarEstado(SLIDE);
				Slide();				
			}
			else if(!ColisionaPared())
			{	
				if(!joystick.b && joystick.up)
				{
					CambiarEstado(JUMP_UP);
					Saltar();
				}				
			}
			else if(!joystick.b)
			{
				CambiarEstado(JUMP_DOWN);
				velocidad.y = 0;
			}
			else if(joystick.b && joystick.left)
			{	
				direccion = Direccion::LEFT;
				if(!ColisionaPared())
				{
					CambiarEstado(Estado::JUMP_AND_RUN_DOWN);
				}								
			}
			else if(!IsJumpStart && joystick.b && joystick.right)
			{	
				direccion = Direccion::RIGHT;
				if(!ColisionaPared())
				{
					CambiarEstado(Estado::JUMP_AND_RUN_DOWN);
				}
								
			}			
			else if(joystick.up)
			{	
				if(!ColisionaTecho())
				{
					CambiarEstado(CLIM_UP);				 
				}
				else
				{
					AjustaColisionY();
				}
			}
			/*else if(joystick.down)
			{
				if(!ColisionaSuelo())
				{
				  CambiarEstado(CLIM_DOWN);				 
				}
				else
				{
					AjustaColisionY();
				}
			}*/
			
			break;
		case CLIM_UP:	
			if(ColisionaTecho())
			{	
				CambiarEstado(CLIM);
				AjustaColisionY();
			}
			else if(!ColisionaPared() || !joystick.up)
			{
				CambiarEstado(Estado::CLIM);				
			}
			else if(!joystick.b)
			{
				CambiarEstado(SLIDE);
				Slide();
			}
			break;
		case CLIM_DOWN:			
			if(!ColisionaPared())
			{
				CambiarEstado(JUMP_DOWN);
			}
			 if(ColisionaSuelo())
			{	
				CambiarEstado(Estado::NORMAL);	
				AjustaColisionY();
				velocidad.y = 0;
			}
			 if(!joystick.b)
			{
				CambiarEstado(SLIDE);
				Slide();
			}
			if(!joystick.down)
			{
				 CambiarEstado(Estado::CLIM);				 
			}
			break;	
		case SLIDE:
			if(!ColisionaPared())
			{
				CambiarEstado(JUMP_DOWN);
			}
			else if(ColisionaSuelo())
			{	
				CambiarEstado(Estado::NORMAL);	
				AjustaColisionY();
				velocidad.y = 0;
			}
			else if(!joystick.b)
			{	
				CambiarEstado(Estado::CLIM);
			}			
			break;
	}

	if(IsJumpStart && !joystick.b)
	{
		IsJumpStart = false;		
	}

	if(IsTirarStart && !joystick.b)
	{
		IsTirarStart = false;
	}

	if(joystick.b && (currentState == Estado::JUMP_UP || currentState == Estado::JUMP_DOWN || 
					  currentState == Estado::JUMP_AND_RUN_UP  || currentState == Estado::JUMP_AND_RUN_DOWN))
	{
		IsJumpStart = true;
	}

	if(joystick.b && currentState == Estado::NORMAL)
	{
		IsTirarStart = true;
	}

	if(currentState == Estado::CLIM_UP)
	{
		Move(0,-CLIM_VEL * dt);
	}

	if(currentState == Estado::CLIM_DOWN)
	{
		Move(0,CLIM_VEL * dt);
	}
		
	if(currentState ==  Estado::RUN || currentState ==  Estado::RUN_AND_ARM1 )
	{	
		Move( GetDireccionX() * velocidad.x * dt, 0);				
	}

	if((currentState ==  Estado::NORMAL || currentState ==  Estado::NORMAL_AND_ARM1) && DelayToBreak())
	{	
		Move(GetDireccionX() *velocidad.x * dt, 0);				
	}

	if(currentState == Estado::JUMP_UP || currentState == Estado::JUMP_DOWN)
	{	
		velocidad.y += gravity*dt;
		Move(0,velocidad.y * dt);						
	}

	 if(currentState == Estado::SLIDE)
	 {
		velocidad.y += gravity*dt;
		Move(0,velocidad.y * dt);
		Move(0,SLIDE_VEL * dt);
	 }

	if(currentState == Estado::JUMP_AND_RUN_UP  || currentState == Estado::JUMP_AND_RUN_DOWN)
	{
		velocidad.y += gravity*dt;
		float vy = velocidad.y * dt;
		float vx = GetDireccionX() *velocidad.x * dt;		
		Move(vx,vy);
	}

	if(currentState == Estado::CRAW_AND_WALK)
	{	
		Move(GetDireccionX() * CRAW_VEL * dt, 0);		
	}

	if(currentState == Estado::SNEAK_AND_RUN)
	{	
		Move(GetDireccionX() * SNEAK_VEL * dt, 0);			
	}
}

void Personaje::DisparoArma1()
{
	if(SecuenciaDisparoFinalizada())
	{
		Disparar(SHOOT_TIME,VEL_MISILES);
	}
}

bool Personaje::VerifyFall()
{	
	if(!ColisionaSuelo())
	{
		CambiarEstado(Estado::JUMP_DOWN);		
		velocidad.y = 0;
		return true;
	}
	return false;
}

bool Personaje::VerifyFallAndRun()
{	
	if(!ColisionaSuelo())
	{
		CambiarEstado(Estado::JUMP_AND_RUN_DOWN);			
		velocidad.y = 0;
		return true;
	}
	return false;
}

bool Personaje::DelayToBreak(bool reset,float value)
{
	if(reset)
	{
		delayToBreak = value;
	}

	if(delayToBreak > 0)
	{
		delayToBreak -= dt;
		return true;
	}
	else
	{
		return false;
	}
}

void Personaje::Saltar(){
	velocidad.y=v0;		
}

void Personaje::Slide()
{
	velocidad.y = SLIDE_VEL;
}

void Personaje::ArrojarPiedra()
{
}
