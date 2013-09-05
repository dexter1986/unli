#include "SpriteBase.h"

SpriteBase::SpriteBase(int cant_estados,const string &filename)
{
	velocidad.x = 0.0f;
	velocidad.y = 0.0f;
	posicion.x = 0.0f;
	posicion.y = 0.0f;
	posicion_inicial.x = 0.0f;
	posicion_inicial.y = 0.0f;
	estado_Actual = 0;
	gravity =  512.0f;
	v0 = -256.0f;
	animaciones = new AnimatedBase[cant_estados];

	const sf::Image &tex = TextureManager::GetInstance().GetTexture(filename);	
	SetImage(tex);

}

SpriteBase::~SpriteBase(void)
{
	delete[] animaciones;
}

void SpriteBase::CambiarEstado(int nuevoEstado, bool continueFromCurrent)
{
	int viejoEstado=estado_Actual;
	estado_Actual=nuevoEstado;
	animaciones[nuevoEstado].Reset();
	if(continueFromCurrent){
		// seteamos el frame de la nueva animacion
		animaciones[nuevoEstado].SetCurrentFrameNum(animaciones[viejoEstado].GetCurrentFrameNum());
		// seteamos el tiempo del frame de la nueva animacion al mismo tiempo que tenia la anterior
		animaciones[nuevoEstado].Animate(animaciones[viejoEstado].GetCurrentFrameElapsedTime());
	}
}

bool SpriteBase::AnimationEnded()
{
	return animaciones[estado_Actual].Ended();
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

	//Anima el objeto
	Internal_Mover_y_Animar();
	
	SetSubRect((animaciones+estado_Actual)->Animate(dt));
}

void SpriteBase::Inicializar()
{
	InicializarAnimaciones();
}
