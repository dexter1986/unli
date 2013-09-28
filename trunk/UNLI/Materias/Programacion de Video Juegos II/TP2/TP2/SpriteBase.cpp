#include "SpriteBase.h"

SpriteBase::SpriteBase(int cant_estados,const string &filename)
{
	
	velocidad.x = 0.0f;
	velocidad.y = 0.0f;
	posicion.x = 0.0f;
	posicion.y = GetPosition().y;
	posicion_inicial.x = 0.0f;
	posicion_inicial.y = 0.0f;
	currentState = 0;
	gravity =  512.0f;
	v0 = -256.0f;
	direccion = Direccion::RIGHT;
	velocidad.y=v0;
	delay = 0;
	animaciones = new AnimatedBase[cant_estados];

	const sf::Image &tex = TextureManager::GetInstance().GetTexture(filename);	
	SetImage(tex);
	//SetScale(0.5,0.5);
}

SpriteBase::~SpriteBase(void)
{
	delete[] animaciones;
}

void SpriteBase::CambiarEstado(int nuevoEstado, bool continueFromCurrent)
{
	int viejoEstado=currentState;
	currentState=nuevoEstado;
	animaciones[nuevoEstado].Reset();	
	if(continueFromCurrent){
		// seteamos el frame de la nueva animacion
		animaciones[nuevoEstado].SetCurrentFrameNum(animaciones[viejoEstado].GetCurrentFrameNum());
		// seteamos el tiempo del frame de la nueva animacion al mismo tiempo que tenia la anterior
		animaciones[nuevoEstado].Animate(animaciones[viejoEstado].GetCurrentFrameElapsedTime());
	}
}

bool SpriteBase::IsAnimationEnded()
{
	return animaciones[currentState].Ended();
}

void SpriteBase::AnimationStop()
{
	animaciones[currentState].Stop();
}

int SpriteBase::AnimationCurrentFrame()
{
	return animaciones[currentState].GetCurrentFrameNum();
}

void SpriteBase::Mover_y_Animar(Joystick j, float dt)
{	
	//Actualiza Delta de tiempo
	this->dt =  dt;
	
	//Actualiza el estado del control
	this->joystick.a =j.a;
	this->joystick.b =j.b;
	this->joystick.down =j.down;
	this->joystick.left =j.left;
	this->joystick.right =j.right;	
	this->joystick.up =j.up;

	Internal_Mover_y_Animar();

	if(direccion == Direccion::RIGHT)
	{
		FlipX(false);				
	}
	else if(direccion == Direccion::LEFT)
	{	
		FlipX(true);				
	}

	if(!DelayTransition())
	{
		//Anima el objeto
		(animaciones+currentState)->Animate(dt);

		SetSubRect(animaciones[currentState].GetCurrentFrameRect());
	
		if(direccion == Direccion::RIGHT)
		{			
			SetCenter(animaciones[currentState].GetCurrentFrameOffset());
		}
		else if(direccion == Direccion::LEFT)
		{
			SetCenter(animaciones[currentState].GetCurrentFrameFlipOffset());
		}
	}
}

bool SpriteBase::DelayTransition(bool reset)
{
	if(reset)
	{
		delay = 0.15;
	}
	
	if(delay > 0)
	{
		delay -= dt;
		return true;
	}else
	{
		return false;
	}
}

void SpriteBase::AnimationReverse(bool reverse)
{
	animaciones[currentState].reverse = reverse;
}

void SpriteBase::Inicializar()
{
	InicializarAnimaciones();
}
