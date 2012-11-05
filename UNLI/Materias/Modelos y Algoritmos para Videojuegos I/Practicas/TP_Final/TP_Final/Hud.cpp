#include"Hud.h"

Hud::Hud(int wnd_width,int wnd_height)
{
	mat_vida.LoadFromFile("..\\Imagenes\\heart.png");
	spr_vida.SetImage(mat_vida);

	width =  (int)spr_vida.GetSize().x;
	height = (int)spr_vida.GetSize().y;

	font.LoadFromFile("..\\Fonts\\Bolstbo_.ttf");

	spr_vida.SetPosition((float)wnd_width / 3 - 80 ,10);

	str_vidas.SetFont(font);
	str_vidas.SetPosition((float)wnd_width / 3 - 40,10);
	str_vidas.SetColor(sf::Color::White);
	str_vidas.SetSize(25);
			
	str_puntos.SetFont(font);
	str_puntos.SetPosition((float)wnd_width / 3 + 200 ,10);
	str_puntos.SetColor(sf::Color::White);
	str_puntos.SetSize(25);	
}

void Hud::Draw(RenderWindow *app)
{
	if(isEnable)
	{
		app->Draw(spr_vida);
		app->Draw(str_vidas);
		app->Draw(str_puntos);
	}
}

void Hud::Enable(bool enable)
{
	isEnable = enable;
}

void Hud::UpdateVidas(int vidas)
{
	vidas_count	 = vidas;
	
	stringstream st_s;
	string str;

	st_s << vidas_count;	
	st_s >> str;
	str = "x " + str;
	
	str_vidas.SetText(str);
}

void Hud::UpdatePuntos(int puntos)
{
	puntos_count = puntos;

	stringstream st_s;
	string str;

	st_s << puntos_count;	
	st_s >> str;
	str = "Puntos: " + str;
	
	str_puntos.SetText(str);
}