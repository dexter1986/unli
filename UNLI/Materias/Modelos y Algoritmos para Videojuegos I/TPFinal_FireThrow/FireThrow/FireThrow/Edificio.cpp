#include "Edificio.h"

Edificio::Edificio():GameObject(false,"..//Imagenes//Edificio_bloque.png")
{	
	Enable(true);
	isInit = false;
}

void Edificio::Init(RenderWindow *app)
{	
	if(!isInit)
	{
		isInit = true;
		GameObject::Init(app);	
		Builder(app->GetWidth(),app->GetHeight());
	}
	else
	{
		for(int w=0;w<mx_w;w++)
		{
			for(int h=0;h<mx_h;h++)
			{	
				bloques[w][h].isActive = false;				
			}
		}
	}

	Make();
}

void Edificio::Update(RenderWindow *app)
{
	GameObject::Update(app);	
}

void Edificio::Draw(RenderWindow *app)
{	
	for(int w=0;w<mx_w;w++)
	{
		for(int h=0;h<mx_h;h++)
		{
			if(bloques[w][h].isActive)
			{
				app->Draw(bloques[w][h].sprite);
			}
		}
	}
}

void  Edificio::Make()
{	
	int maxheight = 0;
	for(int w=0;w<mx_w;w++)
	{	
		if((w >= 0 && w <=2) || (w<=mx_w && w >= mx_w - 3))
		{
			maxheight = rand()%3+1;
		}
		else
		{
			maxheight = rand()%(mx_h-1);
		}
		
		for(int h=0;h<=maxheight;h++)
		{	
			bloques[w][h].isActive = true;			
		}
	}
}

void Edificio::Builder(int p_width,int p_height)
{
	float size_w = width;
	float size_h = height;

	for(int w=0;w<mx_w;w++)
	{
		for(int h=0;h<mx_h;h++)
		{	
			bloques[w][h].isActive = false;
			bloques[w][h].pos_x = size_w * w;
			bloques[w][h].pos_y = p_height - (size_h * (h+1));
			bloques[w][h].sprite.SetImage(*ShareImage());
			bloques[w][h].sprite.SetPosition(bloques[w][h].pos_x,bloques[w][h].pos_y);
		}
	}
}

Vector2f* Edificio::GetPos(bool isPalyer1)
{
	int pos = rand()%3;
	if(isPalyer1)
	{
		pos = pos;
	}
	else
	{
		pos = mx_w - pos - 1;
	}

	for(int h=0;h<mx_h;h++)
	{
		if(!bloques[pos][h].isActive)
		{	
			if(h > 0)
				return new Vector2f(bloques[pos][h-1].pos_x,bloques[pos][h-1].pos_y);	
			else
				return new Vector2f(bloques[pos][h].pos_x,bloques[pos][h].pos_y + bloques[pos][h].sprite.GetSize().y);		
		}
	}
}