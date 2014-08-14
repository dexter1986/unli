#include "SpriteBase.h"

#ifndef round
 #define round(r) r-int(r)>=0.5?int(r)+1:int(r)
#endif

SpriteBase::SpriteBase(int cant_estados,const string &filename,float scale_x,float scale_y,bool NPC)
{
	isNPC = NPC;
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
	isHitWall = false;
	vidas = 5;
	isDead = false;
	isVisible = true;
	pause = false;
	animaciones = new AnimatedBase[cant_estados];
	
	const sf::Image &tex = TextureManager::GetInstance().GetTexture(filename);	
	SetImage(tex);

	SetScale(scale_x,scale_y);

	this->joystick.a = false;
	this->joystick.b = false;
	this->joystick.down = false;
	this->joystick.left = false;
	this->joystick.right = false;	
	this->joystick.up = false;

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
	if(isDead)
		return;
	//Actualiza Delta de tiempo
	this->dt =  dt;
	
	if(!isNPC)
	{
		//Actualiza el estado del control
		this->joystick.a = j.a;
		this->joystick.b = j.b;
		this->joystick.down = j.down;
		this->joystick.left = j.left;
		this->joystick.right = j.right;	
		this->joystick.up = j.up;
	}
	else
	{
		this->joystick.a = false;
		this->joystick.b = false;
		this->joystick.down = false;
		this->joystick.left = false;
		this->joystick.right = false;	
		this->joystick.up = false;

		AiNpc();
	}

	if(!pause)
	{
		Internal_Mover_y_Animar();
	}

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

void SpriteBase::AiNpc()
{
	
}

void SpriteBase::SetOffsetAABB(Vector2f &offset)
{
	//aabb.Offset(-offset.x * scale.x ,-offset.y * scale.y);
}

void SpriteBase::CalculateAABB()
{	
	const Vector2f &pos = GetPosition();
	FloatRect &rec = animaciones[currentState].GetAABB();
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
		delay = 0.15f;
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

	SetPosition(this->nivel->vEntryPoint);	
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
	
	ajustaColision_x = 0;
	ajustaColision_y = 0;

	bool chocaPared = false;
	isHitWall = false;
	
	//// la distancia que nos moveriamos
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
	int tipo=-1;
	chocaPared = nivel->HayColision(aabb_tmp, areaColision,tipo,isNPC);
	
	if(chocaPared)
	{
		isHitWall = true;		
		ResolverColision(tipo,aabb_tmp);



		ajustaColision_x = GetDireccionX() * (dt*velocidad.x-areaColision.GetWidth());


		Move(ajustaColision_x,ajustaColision_y);
	}

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
		int tipo = -1;
		chocaConTecho=nivel->HayColision(aabb_tmp, areaColision,tipo,isNPC);

		if(chocaConTecho)
		{
			ResolverColision(tipo,aabb_tmp);
		}

		ajustaColision_y = despl+areaColision.GetHeight();
	}
	return chocaConTecho;	
}

void SpriteBase::Mover_y_Animar_NPC(float dt)
{
	if(isDead)
		return;
	//Actualiza Delta de tiempo
	this->dt =  dt;

	this->joystick.a =false;
	this->joystick.b =false;
	this->joystick.down =false;
	this->joystick.left =false;
	this->joystick.right =false;	
	this->joystick.up =false;

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

	isVisible = CheckVisibility();

}

// saber si chocara con el suelo cuando esta cayendo,
// o si hay suelo debajo
bool SpriteBase::ColisionaSuelo(){
	bool chocaConSuelo = false;
	ajustaColision_x = 0;
	ajustaColision_y = 0;
	// calculamos la velocidad que tendriamos
	float newvy=velocidad.y + gravity *dt;
	// si estamos subiendo, no podemos chocar con
	// el suelo
	if(newvy>0)
	{
		FloatRect aabb_tmp,areaColision;
		
		if(newvy > MAX_VEL_Y)
		{
			newvy = MAX_VEL_Y;
		}

		// la distancia que nos vamos a mover
		float despl= newvy * dt;

		// conseguimos el AABB actual y calculamos
		// el que tendriamos en un instante de tiempo
		
		aabb_tmp.Top = aabb.Top + despl;
		aabb_tmp.Bottom =  aabb.Bottom + despl;
		aabb_tmp.Left = aabb.Left;
		aabb_tmp.Right = aabb.Right;

		// calculamos si habria colision
		//chocaConSuelo = nivel->HayColision2(aabb,aabb_tmp, areaColision);

		int tipo = -1;
		chocaConSuelo = nivel->HayColision(aabb_tmp, areaColision,tipo,isNPC);

		if(chocaConSuelo)
		{
			ResolverColision(tipo,aabb_tmp);
			ajustaColision_y = despl - areaColision.GetHeight();		
			Move(ajustaColision_x,ajustaColision_y);
		}
	}
	
	return chocaConSuelo;	
}

void SpriteBase::ResolverColision(int tipo,FloatRect aabb_tmp)
{
	//tipo = 1 -> Key
	//tipo = 2 -> Key Bomb
	//tipo = 3 -> Bomb
	if(tipo == 1)
	{
		
	}
	else if(tipo == 2)
	{

	}
	else if(tipo == 3)
	{
		ParticleSystemManager::GetManager().CreateEmiterOneExplosion(aabb_tmp.Left+aabb_tmp.GetWidth()/2,aabb_tmp.Top+aabb_tmp.GetHeight()/2,Color::White);
		isDead = true;
		vidas--;
	}
	else if(tipo == 4)
	{

	}
	else if(tipo >= 10 && tipo <= 19)
	{
		cout<<"Cargar Nivel"<<"\n";
	}
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

void SpriteBase::Draw(sf::RenderWindow &w)
{
	if(isVisible && !isDead)
	{
		w.Draw(*this);
	}
}

bool SpriteBase::CheckVisibility()
{
	Vector2f pos = GetPosition();

	if(pos.x < 0)
		pos.x = 0;
	if(pos.y < 0)
		pos.y = 0;

	FloatRect view = nivel->levelView.GetRect();
	return pos.x > view.Left && pos.x < view.Right && pos.y > view.Top && pos.y < view.Bottom;
}

bool SpriteBase::RecibirImpacto(float x,float y)
{
	if(isVisible)
	{
		if(aabb.Contains(x,y))
		{
			isDead = true;
			vidas--;
			return true;
		}
	}
	return false;
}