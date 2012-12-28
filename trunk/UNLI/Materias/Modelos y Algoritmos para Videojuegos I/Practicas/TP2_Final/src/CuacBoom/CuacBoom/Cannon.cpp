#include "Cannon.h"

Cannon::Cannon()
{
	base = new GameObject(false,"..//Imagenes//Canon_base.png");
	cano = new GameObject(false,"..//Imagenes//Canon_cano.png");

	base->Enable(true);
	cano->Enable(true);

	rot_rad = 0;
}

Cannon::~Cannon()
{
	delete base;
	delete cano;
}

void Cannon::Enable(bool enable)
{

}

void Cannon::Draw(RenderWindow *app) const
{
	cano->Draw(app);
	base->Draw(app);
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

void Cannon::Rotate(float rad)
{
	if(rad > -70 && rad < 70) 
	{	
		cano->Rotate(rad);
	}
}

void Cannon::Init(RenderWindow *app)
{
	 base->Move((app->GetWidth() - base->GetWidth())/2, app->GetHeight() - base->GetHeight() - 50); 
	 cano->SetCenter(cano->GetWidth()/2,cano->GetHeight());
	 cano->Move(app->GetWidth()/2, base->GetPos().y  + base->GetHeight() / 2); 
}