#include "SpriteBase.h"

SpriteBase::SpriteBase(int cant_estados,const string &filename,float scale_x,float scale_y)
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
	scale.x = scale_x;
	scale.y = scale_y;
	
	animaciones = new AnimatedBase[cant_estados];
	
	const sf::Image &tex = TextureManager::GetInstance().GetTexture(filename);	
	SetImage(tex);

	SetScale(scale_x,scale_y);
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
		IntRect rect = animaciones[currentState].GetCurrentFrameRect();
		SetSubRect(rect);
			
		CalculateAABB();		

		if(direccion == Direccion::RIGHT)
		{	
			SetCenter(animaciones[currentState].GetCurrentFrameOffset());
			SetOffsetAABB(animaciones[currentState].GetCurrentFrameOffset());
		}
		else if(direccion == Direccion::LEFT)
		{
			SetCenter(animaciones[currentState].GetCurrentFrameFlipOffset());
			SetOffsetAABB(animaciones[currentState].GetCurrentFrameFlipOffset());
		}
	}
}

void SpriteBase::SetOffsetAABB(Vector2f &offset)
{
	aabb.Offset(-offset.x * scale.x ,-offset.y * scale.y);
}

void SpriteBase::CalculateAABB()
{
	Vector2f pos = GetPosition();
	Vector2f size = GetSize();
	aabb.Top =  pos.y;
	aabb.Left = pos.x;
	aabb.Bottom = aabb.Top + size.y;
	aabb.Right = aabb.Left + size.x;

	aabb.Top += 3.0f * scale.y;
	aabb.Left += 6.0f * scale.x;
	aabb.Right -= 6.0f * scale.x;
	aabb.Bottom -= 2.0f * scale.y;
}

FloatRect &SpriteBase::GetAABB()
{
	return aabb;
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

void SpriteBase::Inicializar(Nivel *n)
{
	InicializarAnimaciones();

	this->nivel = n;
}


// saber si choca con alguna pared por derecha o por izquierda
bool SpriteBase::ChocaraPared(float dt, float &distAjuste){
	//// creamos rectangulos para el bounding box actual
	//// y el area de colision
	//FloatRect aabb, areaColision;
	//
	//// conseguimos el bounding box en la posicion actual
	//aabb=GetAABB();
	//bool chocaPared;
	//
	//// la distancia que nos moveriamos
	//float despl=dt*vx*direccion;
	//
	//// buscamos el bounding box que tendriamos
	//// si nos moviesemos, preguntamos si
	//// colisionamos y la distancia
	//// que nos podriamos mover sin colisionar (ajuste)
	//aabb.Left+=despl;
	//aabb.Right+=despl;
	//// calculamos si habria colision
	//chocaPared=n->HayColision(aabb, areaColision);
	//distAjuste=direccion*(dt*vx-areaColision.GetWidth());
	//return chocaPared;
	return false;
}


// saber si choca con el techo
bool SpriteBase::ChocaraTecho(float dt, float &distAjuste){
	//bool chocaConTecho;
	//// calculamos la velocidad que tendriamos
	//float newvy=vy+gravity*dt;
	//// si estamos cayendo, no podemos chocar con
	//// el suelo
	//if(newvy>0) return false;
	//else{
	//	FloatRect aabb, areaColision;
	//	
	//	// la distancia que nos vamos a mover
	//	float despl=dt*newvy;
	//	
	//	// conseguimos el AABB actual y calculamos
	//	// el que tendriamos en un instante de tiempo
	//	aabb=GetAABB();
	//	aabb=aabb;
	//	aabb.Top+=despl;
	//	aabb.Bottom+=despl;
	//	// calculamos si habria colision
	//	chocaConTecho=n->HayColision(aabb, areaColision);
	//	distAjuste=despl+areaColision.GetHeight();
	//}
	//return chocaConTecho;
	return false;
}


// saber si chocara con el suelo cuando esta cayendo,
// o si hay suelo debajo
bool SpriteBase::ChocaraSuelo(float dt, float &distAjuste){
	bool chocaConSuelo;
	// calculamos la velocidad que tendriamos
	float newvy=velocidad.y+gravity*dt;
	// si estamos subiendo, no podemos chocar con
	// el suelo
	if(newvy<0) return false;
	else{
		FloatRect areaColision;
		
		// la distancia que nos vamos a mover
		float despl=dt*newvy;

		// conseguimos el AABB actual y calculamos
		// el que tendriamos en un instante de tiempo
		
		/*aabb.Top+=despl;
		aabb.Bottom+=despl;*/

		// calculamos si habria colision
		chocaConSuelo=nivel->HayColision(aabb, areaColision);
		distAjuste=despl-areaColision.GetHeight();
		
		//Restauramos el AABB actual
		/*aabb.Top-=despl;
		aabb.Bottom-=despl;*/
	}
	return chocaConSuelo;	
}
