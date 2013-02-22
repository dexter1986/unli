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
		maxheight = rand()%mx_h+1;
		
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
			bloques[w][h].pos_y = p_height - (size_h * h);
			bloques[w][h].sprite.SetImage(*ShareImage());
			bloques[w][h].sprite.SetPosition(bloques[w][h].pos_x,bloques[w][h].pos_y);
		}
	}
}