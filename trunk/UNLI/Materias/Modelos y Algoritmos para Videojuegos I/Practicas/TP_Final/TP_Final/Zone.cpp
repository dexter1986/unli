#include"Zone.h"


void Zone::Enable(bool enable)
{
	isEnable = enable;
}

Zone::Zone(int wnd_width,int wnd_height)
{
	mat.LoadFromFile("..\\Imagenes\\Zone.png");
	zone.SetImage(mat);
	
	rect.Top    = 100.0;
	rect.Left   = 350.0;
	rect.Right  = 450.0;	
	rect.Bottom = 200.0;
}

bool Zone::Hit(FloatRect target)
{
	if(rect.Top < target.Top && rect.Left < target.Left && rect.Bottom > target.Bottom && rect.Right > target.Right)
		return true;
	return false;
}

void Zone::Draw(RenderWindow *app)
{	
	if(isEnable)
	{
		app->Draw(zone);
	}
}

