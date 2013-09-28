#include "Prince.h"

Prince::Prince(void):SpriteBase(25,"personaje.png")
{
	currentState = Estado::NORMAL;	
	direccion = Direccion::RIGHT;
	velocidad.x = 32.0f;
	delayToBreak = 0;
}

Prince::~Prince(void)
{
}

void Prince::InicializarAnimaciones()
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
	animaciones[Estado::NORMAL].SetLoop(false);
	animaciones[Estado::NORMAL].AddFrame(145,285,w,h,framelengh);

	animaciones[Estado::TURN].SetLoop(false);
	animaciones[Estado::TURN].AddFrame(145,285,w,h,0.2);

		
	xo = 272;
	yo = 285;	
	w = 36;
	h = 57;
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

	xo = 209;
	yo = 448;
	w = 42;
	h = 55;
	for(int i=0;i<6;i++)
	{
		animaciones[Estado::RUN_AND_ARM1].AddFrame(xo+w*i,yo,w,h,framelengh,0.0,-2.0,21.0,-2.0);
	}

	xo = 18;
	yo = 301;
	w = 28;
	h = 41;	
	animaciones[Estado::DUCK].SetLoop(false);
	animaciones[Estado::DUCK].AddFrame(xo,yo,w,h,framelengh,0.0,-16.0,0.0,-16.0);

	xo = 58;
	yo = 298;
	w = 31;
	h = 44;		
	animaciones[Estado::DUCK_AND_ARM1].SetLoop(false);
	animaciones[Estado::DUCK_AND_ARM1].AddFrame(xo,yo,w,h,framelengh,1.6,-13.0,0.0,-13.0);
	
	xo = 16;
	yo = 197;
	w = 31;
	h = 62;			
	animaciones[Estado::JUMP_UP].SetLoop(false);
	animaciones[Estado::JUMP_UP].AddFrame(xo,yo,w,h,0.15,0,0,5);
	for(int i=1;i<3;i++)
	{
		animaciones[Estado::JUMP_UP].AddFrame(xo+w*i,yo,w,h,framelengh,0,0,5);
	}

	animaciones[Estado::JUMP_DOWN].SetLoop(false);	
	animaciones[Estado::JUMP_DOWN].AddFrame(xo+w*3,yo,w,h,framelengh,0,0,5);


	xo = 16;
	yo = 197;
	w = 31;
	h = 62;			
	animaciones[Estado::JUMP_AND_RUN_UP].SetLoop(false);
	animaciones[Estado::JUMP_AND_RUN_UP].AddFrame(xo,yo,w,h,0.15,0,0,5);
	for(int i=1;i<3;i++)
	{
		animaciones[Estado::JUMP_AND_RUN_UP].AddFrame(xo+w*i,yo,w,h,framelengh,0,0,5);
	}

	animaciones[Estado::JUMP_AND_RUN_DOWN].SetLoop(false);	
	animaciones[Estado::JUMP_AND_RUN_DOWN].AddFrame(xo+w*3,yo,w,h,framelengh,0,0,5);
	
	
}

void Prince::Internal_Mover_y_Animar()
{
	switch(currentState)
	{
		case TURN:
			if(IsAnimationEnded())
			{
				CambiarEstado(Estado::NORMAL);
			}
		break;
		case NORMAL:
			if(joystick.right)
			{	
				if(direccion != Direccion::RIGHT)
				{
					CambiarEstado(Estado::TURN);
				}
				else
				{
					CambiarEstado(Estado::RUN);						
				}
				direccion = Direccion::RIGHT;
			}
			if(joystick.left)
			{
				if(direccion != Direccion::LEFT)
				{
					CambiarEstado(Estado::TURN);
				}
				else
				{
					CambiarEstado(Estado::RUN);								
				}
				direccion = Direccion::LEFT;
			}
			if(joystick.down)
			{	
				CambiarEstado(Estado::DUCK);
			}
			if(joystick.a)
			{	
				CambiarEstado(Estado::NORMAL_AND_ARM1);
			}
			if(joystick.up)
			{
				CambiarEstado(Estado::JUMP_UP);
				Saltar();
			}
			break;
		case NORMAL_AND_ARM1:
			if(!joystick.a)
			{
				CambiarEstado(Estado::NORMAL);
			}
			if(joystick.down)
			{
				CambiarEstado(Estado::DUCK_AND_ARM1);
			}
			if(joystick.left)
			{
				CambiarEstado(Estado::RUN);
				direccion = Direccion::LEFT;
			}
			if(joystick.right)
			{
				CambiarEstado(Estado::RUN);
				direccion = Direccion::RIGHT;
			}
			//DisparoArma1();
			break;
		case RUN:
			if(!joystick.right && direccion == Direccion::RIGHT || !joystick.left && direccion == Direccion::LEFT)
			{	
				DelayToBreak(true);
				CambiarEstado(Estado::NORMAL);				
			}
			if(joystick.a)
			{
				CambiarEstado(Estado::RUN_AND_ARM1,true);
			}
			if(joystick.up)
			{
				CambiarEstado(Estado::JUMP_AND_RUN_UP);
				Saltar();
			}
			break;
		case RUN_AND_ARM1:
			if(!joystick.a)
			{
				DelayToBreak(true);
				CambiarEstado(Estado::RUN,true);
			}
			if(!joystick.right && direccion == Direccion::RIGHT || !joystick.left && direccion == Direccion::LEFT)
			{
				CambiarEstado(Estado::NORMAL);
			}
			if(joystick.up)
			{
				CambiarEstado(Estado::JUMP_AND_RUN_UP);
				Saltar();
			}
			//DisparoArma1();
			break;
		case DUCK:
			if(!joystick.down)
			{
				CambiarEstado(Estado::NORMAL);
			}	
			if(joystick.left)
			{
				direccion = Direccion::LEFT;
			}
			if(joystick.right)
			{
				direccion = Direccion::RIGHT;
			}
			if(joystick.a)
			{
				CambiarEstado(Estado::DUCK_AND_ARM1);
			}
			break;		
		case DUCK_AND_ARM1:
			if(!joystick.a)
			{
				CambiarEstado(Estado::DUCK);
			}
			if(!joystick.down)
			{
				CambiarEstado(Estado::NORMAL_AND_ARM1);
			}
			if(joystick.left)
			{
				direccion = Direccion::LEFT;
			}
			if(joystick.right)
			{
				direccion = Direccion::RIGHT;
			}
			//DisparoArma1();
			break;	
		case JUMP_UP:
			if(velocidad.y > 0)
			{
				CambiarEstado(Estado::JUMP_DOWN);
			}
			break;
		case JUMP_DOWN:
			if(ColisionaConSuelo())
			{
				CambiarEstado(Estado::NORMAL);
			}
			break;
		case JUMP_AND_RUN_UP:
			if(velocidad.y > 0)
			{
				CambiarEstado(Estado::JUMP_AND_RUN_DOWN);
			}
			break;
		case JUMP_AND_RUN_DOWN:
			if(ColisionaConSuelo())
			{
				CambiarEstado(Estado::NORMAL);
			}
			break;
			
	}

	// segun el estado, movemos horizontalmente
	if(currentState ==  Estado::RUN || currentState ==  Estado::RUN_AND_ARM1 )
	{	
		if(direccion == Direccion::LEFT)
			Move(-velocidad.x * dt, 0);		
		else if(direccion == Direccion::RIGHT)
			Move(velocidad.x * dt, 0);		
	}

	if((currentState ==  Estado::NORMAL || currentState ==  Estado::NORMAL_AND_ARM1) && DelayToBreak())
	{	
		if(direccion == Direccion::LEFT)
			Move(-velocidad.x * dt, 0);		
		else if(direccion == Direccion::RIGHT)
			Move(velocidad.x * dt, 0);		
	}

	if(currentState == Estado::JUMP_UP || currentState == Estado::JUMP_DOWN )
	{
		velocidad.y += gravity*dt;
		Move(0,velocidad.y * dt);				
	}

	if(currentState == Estado::JUMP_AND_RUN_UP  || currentState == Estado::JUMP_AND_RUN_DOWN)
	{
		velocidad.y += gravity*dt;
		float vy = velocidad.y * dt;
		float vx = 0;
		if(direccion == Direccion::LEFT)
			vx = -velocidad.x * dt;
		else if(direccion == Direccion::RIGHT)
			vx = velocidad.x * dt;
		Move(vx,vy);
	}


	//else if(estado_Actual == PARAR && direccion == -1){
	//	vx -= 2.0f;
	//	if(vx < 0)
	//		vx = 0;
	//	Move(direccion * vx * dt, 0);		
	//}

	//// segun el estado, movemos verticalmente
	//if(estado_Actual == TREPANDO){		
	//	vy+=gravity*dt;
	//	Move(0, vy*dt);		
	//}	
		

}

bool Prince::DelayToBreak(bool reset,float value)
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

void Prince::Saltar(){
	velocidad.y=v0;	
	posicion.y=GetPosition().y;
}

// detecta si hubo colision con el suelo y ajusta la coordenada y del sprite
bool Prince::ColisionaConSuelo(){
	if(GetPosition().y >= posicion.y){
		// si hubo colision con el suelo, puede haber ocurrido
		// interpenetracion, por lo que es necesario ajustar
		// la coordenada y a la del suelo que guardamos antes
		SetY(posicion.y);
		return true;
	}else{
		return false;
	}
}