#include"Letra.h"


void Letra::Enable(bool enable)
{
	isEnable = enable;
}

Letra::Letra(int wnd_width,int wnd_height,float iter)
{
	ciclo = iter;
	velocidad = 120.0f * ciclo;
	width = wnd_width;
	height = wnd_height;

	font.LoadFromFile("..\\Fonts\\Bolstbo_.ttf");
	str_letra.SetFont(font);	
	str_letra.SetColor(sf::Color::White);
	str_letra.SetSize(70);

	RndLetter();
	
	pos_x = width / 2.0f ;
	pos_y = (float)wnd_height;

	str_letra.SetPosition(pos_x,pos_y);
	
	pos_x = (width - (str_letra.GetRect().Right - str_letra.GetRect().Left))/2;

	str_letra.SetPosition(pos_x,pos_y);

	count = 0.4f;
	iter_max = 2.0f;
}

void Letra::Draw(RenderWindow *app)
{
	if(isEnable)
		app->Draw(str_letra);
}

void Letra::Update(RenderWindow *app)
{
	if(isEnable)
	{
		if( pos_y > 105)
		{
			float d =  velocidad * app->GetFrameTime();	
			pos_y -= d;
			str_letra.SetPosition(pos_x,pos_y);
		}
		else
		{
			count -= app->GetFrameTime();
			if(count < 0)
				Enable(false);
		}
	}
}

bool Letra::Enable()
{
	return isEnable;
}

void Letra::Reset()
{
	count = 0.4f;
	velocidad = 120.0f * ciclo;
	pos_y = (float)height;
	RndLetter();
	str_letra.SetPosition(pos_x,pos_y);
	pos_x = (width - (str_letra.GetRect().Right - str_letra.GetRect().Left))/2;
	str_letra.SetPosition(pos_x,pos_y);
	Enable(true);

	if(iter_max < 0)
	{
		ciclo += 0.15f;
		iter_max = 2;

		if(count > 0.2)
			count -= 0.01f;
	}
	
	iter_max--;
}

void Letra::RndLetter()
{
	int aux = rand()%26 + 97;		
	letra = (char) (aux - 32);
	str_letra.SetText(letra);
	letra = (char) aux;
}

FloatRect Letra::GetRect()
{
	return str_letra.GetRect();
}

bool Letra::Compare(char a)
{
	string aux;
	aux = a;
	if(letra.compare(aux)==0)
		return true;
	return false;
}