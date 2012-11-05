#include"Circulo.h"

Circulo::Circulo(int wnd_width,int wnd_height)
{
	
	img.LoadFromFile("..\\Imagenes\\rcircle.png");
	sprite.SetImage(img);

	width =  (int)sprite.GetSize().x;
	height = (int)sprite.GetSize().y;

	pos[0].x = 10;
	pos[0].y = 10;

	pos[1].x = (float)wnd_width-width-10;
	pos[1].y = 10;
	
	pos[2].x = 10;
	pos[2].y = (float)wnd_height-height-10;
	
	pos[3].x = (float)wnd_width-width-10;
	pos[3].y = (float)wnd_height-height-10;
	
	Circulo::NexPos();
	ResetTime();	
}

void Circulo::ResetTime()
{	
	time_count = 0;
	Circulo::NexPos();

	if(isEnable)
		time_frec =(float) (rand()%2 + 1);
	else
		time_frec =(float) (rand()%5 + 2);
}

void Circulo::Draw(RenderWindow *app)
{
	if(isEnable)
		app->Draw(sprite);
}

void Circulo::NexPos(){
	index_pos = rand()%4;
	sprite.SetPosition(pos[index_pos]);
}

bool Circulo::Hit(int x,int y)
{	
	if(!isEnable)
		return false;

	if(pos[index_pos].x < x && pos[index_pos].x + width > x && pos[index_pos].y < y && pos[index_pos].y + height > y)
	{
		Circulo::Enable(false);
		return true;
	}
	return false;
}

void Circulo::Enable(bool enable)
{
	isEnable = enable;
	ResetTime();
}

void Circulo::Update(RenderWindow *app)
{
	time_count += app->GetFrameTime();
	if(time_count > time_frec)
	{
		if(isEnable)
		{
			Circulo::Enable(false);
		}else
		{
			Circulo::Enable(true);
		}
	}
}