#include "Hud.h"
#include "Helper.h"

Hud::Hud()
{
	font.LoadFromFile("..//Fonts//ethnocen.ttf",24);
	text.SetFont(font);
	initFXTime = 0;
}

void Hud::Init(RenderWindow *app)
{	
	text.SetColor(Color::White);
	text.SetSize(30);
	isTurnoPlayer1 = true;
	isCleanPlayer1 = false;
	isCleanPlayer2 = false;
	isCleanPuntos = false;
	isSetVel = false;
	isSetAng = true;
	windForce = 0;
	estado = 0;
    cantjugadores = 1;
	puntos = 3;
	nomplayer1 = "Jugador 1";
	nomplayer2 = "Jugador 2";
	cantPuntos = "_ _ _";
	playerstate[0].nombre = "_ _ _ _ _ _";
	playerstate[0].angulo = 0;
	playerstate[0].puntos = 0;
	playerstate[0].velocidad = 0;

	playerstate[1].nombre = "_ _ _ _ _ _";
	playerstate[1].angulo = 0;
	playerstate[1].puntos = 0;
	playerstate[1].velocidad = 0;
}

void Hud::Draw(RenderWindow *app)
{
	if(estado == 0)
	{
		SeleccionJugadores(app);		
	}
	else if(estado == 1 || estado == 2 || estado == 3)
	{
		NombreJugadores(app);		
	}
	else if(estado == 4)
	{
		HudUser(app);
	}
}

void Hud::SeleccionJugadores(RenderWindow *app)
{
	text.SetText(L"1  Jugador\n\n2 Jugadores");
	text.SetPosition(250,250);
	app->Draw(text);	
	app->Draw(Shape::Rectangle(tx,ty,bx,by,Color::Color(0,0,0,0),3.0f,Color::White));	
}

void Hud::NombreJugadores(RenderWindow *app)
{	
	string aux;
	
	if(estado == 1)
	{
		aux = "Nombre: ";
		aux += nomplayer1;
		aux += "\n\n";
		aux += playerstate[0].nombre;
	}
	else if(estado == 2)
	{
		aux = "Nombre: ";
		aux += nomplayer2;
		aux += "\n\n";
		aux += playerstate[1].nombre;
	}
	else if( estado == 3)
	{
		aux = "Vidas: ";
		aux += Helper::ToInt(puntos);
		aux += "\n\n";
		aux += cantPuntos;
	}
	text.SetText(aux);
	text.SetPosition(150,100);
	app->Draw(text);	
	
}

void Hud::HudUser(RenderWindow *app)
{
	string aux;

	aux += playerstate[0].nombre;
	aux += "\n";
	aux += "Angulo: ";
	aux += Helper::ToInt((int)playerstate[0].angulo);
	if(isTurnoPlayer1 && isSetAng)
		aux += " <--";
	aux += "\n";
	aux += "Velocidad: ";
	aux += Helper::ToInt((int)playerstate[0].velocidad);
	if(isTurnoPlayer1 && isSetVel)
		aux += " <--";
	aux += "\n";
		
	text.SetText(aux);
	text.SetPosition(0,0);
	app->Draw(text);


	aux = playerstate[1].nombre;
	aux += "\n";
	if(!isTurnoPlayer1 && isSetAng)
		aux += "--> ";
	aux += "Angulo: ";
	aux += Helper::ToInt((int)playerstate[1].angulo);
	aux += "\n";
	if(!isTurnoPlayer1 && isSetVel)
		aux += "--> ";
	aux += "Velocidad: ";
	aux += Helper::ToInt((int)playerstate[1].velocidad);
	aux += "\n";
		
	text.SetText(aux);
	text.SetPosition(600,0);
	app->Draw(text);

	aux = Helper::ToInt(playerstate[0].puntos);
	aux += " > Vidas < ";	
	aux += Helper::ToInt(playerstate[1].puntos);	
	
	text.SetText(aux);
	text.SetPosition(300,0);
	app->Draw(text);

	/*if(isTurnoPlayer1)
	{
		aux = playerstate[0].nombre;
		aux += " < Turno";
		text.SetPosition(250,15);
	}
	else
	{		
		aux = "Turno > ";
		aux += playerstate[1].nombre;
		text.SetPosition(300,15);
	}
		
	text.SetText(aux);	
	app->Draw(text);
*/
	int wind = (int)abs(windForce);
	if(wind>0)
	{
		aux = "Viento ";

		if(windForce > 0)
			aux += "<";

		if(wind > 2)
			aux +="-";
		if(wind > 5)
			aux +="-";
		if(wind > 7)
			aux +="-";		
		if(wind > 10)
			aux +="=";
		if(wind > 15)
			aux +="=";
		if(wind > 20)
			aux +="=";
		if(wind > 25)
			aux +="=";
		if(wind > 30)
			aux +="=";
		if(wind > 35)
			aux +="=";
		if(wind > 40)
			aux +="=";	

		if(windForce < 0)
			aux += ">";
	
		text.SetPosition(300,35);
			
		text.SetText(aux);	
		app->Draw(text);
	}
	
}

int Hud::GetVidas()
{
	return puntos;
}

void Hud::SetStatePlayer1(float angulo,float velocidad,int puntos)
{
	playerstate[0].angulo = angulo;
	playerstate[0].velocidad = velocidad;
	playerstate[0].puntos = puntos;
}

void Hud::SetStatePlayer2(float angulo,float velocidad,int puntos)
{
	playerstate[1].angulo = angulo;
	playerstate[1].velocidad = velocidad;
	playerstate[1].puntos = puntos;
}

int Hud::GetCantJugadores()
{
	return cantjugadores;
}

bool Hud::ShowLostVida(RenderWindow *app,bool isPlayer1)
{
	initFXTime += app->GetFrameTime();
	if(initFXTime > MAX_FX_TIME)
	{
		return true;
	}else
	{
		string aux;
	
		text.SetPosition(300,150);
	
		if(isPlayer1)
			aux = playerstate[0].nombre;
		else
			aux = playerstate[1].nombre;

		aux += " PIERDE";

		text.SetColor(Color::Red);
		text.SetText(aux);

		app->Draw(text);				
		text.SetColor(Color::Black);
		return false;
	}
}

void Hud::InitFXTime()
{
	initFXTime = 0;
}

void Hud::ProcessEvent(Event &evt)
{
	if(evt.Type == Event::KeyPressed)
	{
		if(estado == 1)
		{
			if(evt.Key.Code == Key::Return)
			{
				if(cantjugadores > 1)
				{
					estado = 2;
				}
				else
				{
					estado = 3;
					playerstate[1].nombre = "Maquina";
				}

				if(!isCleanPlayer1)
				{	
					playerstate[0].nombre = nomplayer1.c_str();
				}
				return;
			}
			if(evt.Key.Code == Key::Back)
			{
				if(!playerstate[0].nombre.empty())
				{
					playerstate[0].nombre.erase(playerstate[0].nombre.length()-1,1);
				}
			}
			else
			{
				if(!isCleanPlayer1)
				{
					isCleanPlayer1 = true;
					playerstate[0].nombre = evt.Key.Code;
				}
				else
				{	
					playerstate[0].nombre += evt.Key.Code;
				}
			}
		}
		else if(estado == 2)
		{
			if(evt.Key.Code == Key::Return)
			{
				estado = 3;
				if(!isCleanPlayer2)
				{
					playerstate[1].nombre = nomplayer2.c_str();
				}
				return;
			}
			if(evt.Key.Code == Key::Back)
			{
				if(!playerstate[1].nombre.empty())
				{
					playerstate[1].nombre.erase(playerstate[1].nombre.length()-1,1);
				}
			}
			else
			{
				if(!isCleanPlayer2)
				{
					isCleanPlayer2 = true;
					playerstate[1].nombre = evt.Key.Code;
				}
				else
				{	
					playerstate[1].nombre += evt.Key.Code;
				}
			}
		}
		else if(estado == 3)
		{
			if(evt.Key.Code == Key::Return)
			{
				estado = 4;
				text.SetColor(Color::Black);
				text.SetSize(12);
				if(!isCleanPuntos)
				{
					cantPuntos = puntos;
				}
				else
				{
					puntos = Helper::ToString(cantPuntos);
				}

				playerstate[0].puntos = puntos;
				playerstate[1].puntos = puntos;

				return;
			}
			if(evt.Key.Code == Key::Back)
			{
				if(!playerstate[1].nombre.empty())
				{
					cantPuntos.erase(cantPuntos.length()-1,1);
				}
			}
			else if(evt.Key.Code == Key::Num0 ||evt.Key.Code == Key::Num1 || evt.Key.Code == Key::Num2 ||
				    evt.Key.Code == Key::Num3 ||evt.Key.Code == Key::Num4 || evt.Key.Code == Key::Num5 ||
					evt.Key.Code == Key::Num6 ||evt.Key.Code == Key::Num7 || evt.Key.Code == Key::Num8 ||
					evt.Key.Code == Key::Num9)
			{
				if(!isCleanPuntos)
				{
					isCleanPuntos = true;
					cantPuntos = evt.Key.Code;
				}
				else
				{	
					cantPuntos += evt.Key.Code;
				}
			}
		}
	}
}

bool Hud::Hit(int x,int y)
{
	bool ret = false;

	if(estado == 0)
	{
		//1 Jugador
		if(x >= 248 && y >= 252 && x <= 515 && y <= 285 )
		{
			cantjugadores = 1;
			estado = 1;
			ret = true;
		}//2 Jugadores
		else if(x >= 248 && y >= 314 && x <= 572 && y <= 344 )
		{
			cantjugadores = 2;
			estado = 1;
			ret = true;
		}
	}
	return ret;
}

bool Hud::Test(int x,int y)
{
	bool ret = false;
	tx = 0;
	ty = 0;
	bx = 0;
	by = 0;

	if(estado == 0)
	{
		//1 Jugador
		if(x >= 248 && y >= 252 && x <= 515 && y <= 285 )
		{
			tx = 248;
			ty = 252;
			bx = 515;
			by = 285;
			ret = true;
		}//2 Jugadores
		else if(x >= 248 && y >= 314 && x <= 572 && y <= 344 )
		{
			tx = 248;
			ty = 314;
			bx = 572;
			by = 344;
			ret = true;
		}
	}
	
	return ret;
}

int Hud::GetState()
{
	return estado;
}

void Hud::SetTurno(bool isPlayer1)
{
	isTurnoPlayer1 = isPlayer1;
}

void Hud::SetWind(float value)
{
	windForce = value;
}

void Hud::InitLevel()
{
	playerstate[0].angulo = 0;
	playerstate[0].puntos = puntos;
	playerstate[0].velocidad = 0;

	playerstate[1].angulo = 0;
	playerstate[1].puntos = puntos;
	playerstate[1].velocidad = 0;
}

void Hud::SetIsVel()
{
	isSetAng = false;
	isSetVel = true;
}

void Hud::SetIsAng()
{
	isSetAng = true;
	isSetVel = false;
}

void Hud::SetIsFire()
{
	isSetAng = false;
	isSetVel = false;
}

void Hud::ShowGano(RenderWindow *app,bool isPlayer1)
{
	string aux;
	
	text.SetPosition(300,150);
	
	if(isPlayer1)
		aux = playerstate[0].nombre;
	else
		aux = playerstate[1].nombre;

	aux += " GANA";

	
	text.SetText(aux);	
	app->Draw(text);


	text.SetPosition(250,200);
	aux = "Presionar Enter para continuar";
	text.SetText(aux);	
	app->Draw(text);
}