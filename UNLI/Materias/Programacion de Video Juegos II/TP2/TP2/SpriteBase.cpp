#include "SpriteBase.h"

#ifndef round
 #define round(r) r-int(r)>=0.5?int(r)+1:int(r)
#endif

SpriteBase::SpriteBase(int cant_estados,const string &filename,float scale_x,float scale_y)
{
	
	velocidad.x = 0.0f;
	velocidad.y = 0.0f;
	posicion.x = 0.0f;
	posicion.y = GetPosition().y;
	posicion_inicial.x = 0.0f;
	posicion_inicial.y = 0.0f;
	currentState = 0;
	gravity = 512.0f;
	v0 = -256.0f;
	direccion = Direccion::RIGHT;
	velocidad.y=v0;
	delay = 0;
	ajustaColision_x = 0;
	ajustaColision_y = 0;
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

void SpriteBase::Disparar(float shootTime,float vel_misiles)
{	
	Vector2f pos = GetPosition();
	IntRect rect = animaciones[currentState].GetCurrentFrameRect();
	Vector2f vect = animaciones[currentState].GetCurrentFrameOffset();
	if(direccion == Direccion::RIGHT)
	{
		Disparar(aabb.Right , aabb.Top + aabb.GetHeight()/4-2 ,shootTime,vel_misiles);
	}
	else if(direccion == Direccion::LEFT)
	{
		Disparar(aabb.Left , aabb.Top + aabb.GetHeight()/4-2 ,shootTime,vel_misiles);
	}
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

		CalculateAABB();
	}

	if(!SecuenciaDisparoFinalizada()) shootTime-=dt;
}

void SpriteBase::SetOffsetAABB(Vector2f &offset)
{
	//aabb.Offset(-offset.x * scale.x ,-offset.y * scale.y);
}

void SpriteBase::CalculateAABB()
{	
	Vector2f pos = GetPosition();
	FloatRect rec = animaciones[currentState].GetAABB();
	aabb.Top =  pos.y + rec.Top;
	aabb.Left = pos.x + rec.Left;
	aabb.Bottom = pos.y + rec.Bottom;
	aabb.Right = pos.x + rec.Right;
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

void SpriteBase::Inicializar(ManejadorDisparos *d,Nivel *n)
{
	InicializarAnimaciones();

	this->nivel = n;
	this->disparos = d;
}

// para saber si ya expiro el tiempo que dura la secuencia de disparo
bool SpriteBase::SecuenciaDisparoFinalizada(){
	return shootTime<0;
}

void SpriteBase::Disparar(float x, float y,float shoot_time,float velmisiles){
	shootTime=shoot_time;
	disparos->AgregarDisparo(x, y, velmisiles*GetDireccionX());
}

// saber si choca con alguna pared por derecha o por izquierda
bool SpriteBase::ColisionaPared(){
	// creamos rectangulos para el bounding box actual
	// y el area de colision
	FloatRect aabb_tmp, areaColision;
	
	bool chocaPared = false;
	
	// la distancia que nos moveriamos
	float despl = GetDireccionX() * dt * velocidad.x;
	
	// buscamos el bounding box que tendriamos
	// si nos moviesemos, preguntamos si
	// colisionamos y la distancia
	// que nos podriamos mover sin colisionar (ajuste)
	aabb_tmp.Left =  aabb.Left + despl;
	aabb_tmp.Right = aabb.Right + despl;
	aabb_tmp.Top = aabb.Top;
	aabb_tmp.Bottom = aabb.Bottom;
	
	// calculamos si habria colision
	//chocaPared=nivel->HayColision2(aabb, aabb_tmp, areaColision);
	chocaPared = nivel->HayColision(aabb_tmp, areaColision);
	
	ajustaColision_x = GetDireccionX() * (dt*velocidad.x-areaColision.GetWidth());

	return chocaPared;	
}

// saber si choca con el techo
bool SpriteBase::ColisionaTecho(){
	bool chocaConTecho = false;
	// calculamos la velocidad que tendriamos
	float newvy=velocidad.y+gravity*dt;
	// si estamos cayendo, no podemos chocar con
	// el suelo
	if(newvy<0)
	{
		FloatRect aabb_tmp, areaColision;
		
		// la distancia que nos vamos a mover
		float despl=dt*newvy;
		
		// conseguimos el AABB actual y calculamos
		// el que tendriamos en un instante de tiempo
		aabb_tmp.Bottom = aabb.Bottom + despl;
		aabb_tmp.Top = aabb.Top + despl;
		aabb_tmp.Left = aabb.Left;
		aabb_tmp.Right = aabb.Right;
		
		// calculamos si habria colision
		chocaConTecho=nivel->HayColision(aabb_tmp, areaColision);
		ajustaColision_y = despl+areaColision.GetHeight();
	}
	return chocaConTecho;	
}

// saber si chocara con el suelo cuando esta cayendo,
// o si hay suelo debajo
bool SpriteBase::ColisionaSuelo(){
	bool chocaConSuelo = false;
	ajustaColision_x = 0;
	ajustaColision_y = 0;
	// calculamos la velocidad que tendriamos
	float newvy=velocidad.y+gravity*dt;
	// si estamos subiendo, no podemos chocar con
	// el suelo
	if(newvy>0)
	{
		FloatRect aabb_tmp,areaColision;
		
		// la distancia que nos vamos a mover
		float despl= dt * newvy;

		// conseguimos el AABB actual y calculamos
		// el que tendriamos en un instante de tiempo
		
		aabb_tmp.Top = aabb.Top + despl;
		aabb_tmp.Bottom =  aabb.Bottom + despl;
		aabb_tmp.Left = aabb.Left;
		aabb_tmp.Right = aabb.Right;

		// calculamos si habria colision
		//chocaConSuelo = nivel->HayColision2(aabb,aabb_tmp, areaColision);
		chocaConSuelo = nivel->HayColision(aabb_tmp, areaColision);

		ajustaColision_y = despl - areaColision.GetHeight();					
	}
	
	return chocaConSuelo;	
}

void SpriteBase::AjustaColisionX()
{	
	Move(ajustaColision_x, 0);					
}

void SpriteBase::AjustaColisionY()
{
	Move(0, ajustaColision_y);
}

int SpriteBase::GetDireccionX()
{
	if(direccion == Direccion::LEFT)
			return -1;
	else if(direccion == Direccion::RIGHT)
			return 1;
}
