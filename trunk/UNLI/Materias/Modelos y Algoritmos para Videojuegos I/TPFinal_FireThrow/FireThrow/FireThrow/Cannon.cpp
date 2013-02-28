#include "Cannon.h"

Cannon::Cannon()
{
	base = new GameObject(true,"..//Imagenes//Canon_base.png");
	cano = new GameObject(true,"..//Imagenes//Canon_cano.png");

	base->Enable(true);
	cano->Enable(true);
	blink_draw = false;
	rot_rad = 0;
}

Cannon::~Cannon()
{
	delete base;
	delete cano;
}

void Cannon::Enable(bool enable)
{
	cano->Enable(enable);
	base->Enable(enable);	
}

void Cannon::Draw(RenderWindow *app) const
{
	cano->Draw(app);
	base->Draw(app);
}

void Cannon::Blink(RenderWindow *app)
{
	if(blink_draw)
	{
		cano->Draw(app);
		base->Draw(app);
	}
	blink_draw = !blink_draw;
}

bool Cannon::Hit(int x,int y) const
{
	return false;
}

void Cannon::Update(RenderWindow *app)
{
	
}

void Cannon::Move(float x,float y)
{

}

int Cannon::GetVidas()
{
	return vidas;
}

void Cannon::SetVelocidad(float value)
{
	velocidad = value;
}

void Cannon::SetAngulo(float value)
{
	angulo = value;
}

void Cannon::SetVidas(int value)
{
	vidas = value;
}

float Cannon::GetVelocidad()
{
	return velocidad;
}

float Cannon::GetAngulo()
{
	return angulo;
}

bool Cannon::Fire(bool leftSide)
{
	if(angulo > 180)
		angulo = 180;

	float aux = angulo;

	if(leftSide)
	{
		aux = (90-aux) *-1;
	}
	else
	{
		aux = 90-aux;
	}

	Rotate(aux);
	return true;
}

void Cannon::Rotate(float rad)
{
	rot_rad = rad;
	cano->Rotate(rot_rad);
}

Vector2f Cannon::GetLargoCano() const
{
	return Vector2f(cano->GetWidth(),cano->GetHeight());
}

void Cannon::Init(RenderWindow *app)
{

}

void Cannon::Init(RenderWindow *app,Vector2f *pos)
{	
	 base->Move(pos->x + base->GetWidth() / 2.0f - 17.0f ,pos->y - base->GetHeight()); 
	 cano->Move(base->GetPos().x  + base->GetWidth() / 2.0f, base->GetPos().y  + base->GetHeight() / 2.0f); 
	 cano->SetCenter(cano->GetWidth()/2.0f,cano->GetHeight());	
}

bool Cannon::Hit(Vector2f pos)
{
	bool ret = false;
	if(cano->Hit(pos.x,pos.y))
		ret = true;
	else if(base->Hit(pos.x,pos.y))
		ret = true;

	if(ret)
		vidas--;

	return ret;
}

float Cannon::GetRad() const
{
	return rot_rad;
}

Vector2f Cannon::GetPosCano() const
{
	return cano->GetPos();
}

Vector2f Cannon::GetPos() const
{
	return base->GetPos();
}

Vector2f Cannon::GetSize() const
{
	return Vector2f(base->GetWidth(),base->GetHeight());
}