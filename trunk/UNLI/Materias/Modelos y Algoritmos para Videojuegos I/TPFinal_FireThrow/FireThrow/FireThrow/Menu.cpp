#include "Menu.h"

Menu::Menu():GameObject(false,"..//Imagenes//Menu.png",5)
{	
	Enable(true);
}

void Menu::Init(RenderWindow *app)
{
	tx,ty,bx,by = 0;
	SetMenu(MENU_TYPE::GENERAL);
	menustate = MENU_STATE::MENU;
	GameObject::Init(app);		
}

void Menu::Update(RenderWindow *app)
{
	GameObject::Update(app);	
}

void Menu::Draw(RenderWindow *app)
{	
	GameObject::Draw(app);	
	app->Draw(Shape::Rectangle(tx,ty,bx,by,Color::Color(0,0,0,0),3.0f,Color::White));
}

void Menu::SetMenu(MENU_TYPE type)
{
	switch(type)
	{
	case MENU_TYPE::GENERAL:
		currentframe = 0;
		break;
	case MENU_TYPE::PAUSA:
		currentframe = 1;
		break;
	case MENU_TYPE::PLAY_AGAIN:
		currentframe = 2;
		break;
	case MENU_TYPE::M_CREDITOS:
		currentframe = 3;
		break;
	case MENU_TYPE::M_AYUDA:
		currentframe = 4;
		break;
	}
	menutype = type;
	UpdateFrame();
}

Menu::MENU_STATE Menu::GetState()
{
	return menustate;
}

bool Menu::Test(int x,int y,bool isTest)
{
	bool ret = false;
	tx = 0;
	ty = 0;
	bx = 0;
	by = 0;
	if(menutype == MENU_TYPE::GENERAL)
	{
		//JUGAR
		if(x >= 336 && y >= 200 && x <= 468 && y <= 225 )
		{
			if(!isTest ){
				menustate = MENU_STATE::JUGAR;			
				SetMenu(MENU_TYPE::PAUSA);
			}
			tx = 334;
			ty = 198;
			bx = 470;
			by = 232;
			ret = true;
		}//AYUDA
		else if(x >= 330 && y >= 250 && x <= 470 && y <= 270 )
		{
			if(!isTest ){
				menustate = MENU_STATE::AYUDA;
				SetMenu(MENU_TYPE::M_AYUDA);
			}
			tx = 329;
			ty = 244;
			bx = 474;
			by = 276;
			ret = true;
		}//CREDITOS
		else if(x >= 310 && y >= 300 && x <= 490 && y <= 320 )
		{
			if(!isTest ){
				menustate = MENU_STATE::CREDITOS;
				SetMenu(MENU_TYPE::M_CREDITOS);
			}
			tx = 306;
			ty = 293;
			bx = 494;
			by = 325;
			ret = true;
		}//SALIR
		else if(x >= 350 && y >= 345 && x <= 460 && y <= 360 )
		{
			if(!isTest )
				menustate = MENU_STATE::SALIR;
			tx = 345;
			ty = 330;
			bx = 464;
			by = 363;
			ret = true;
		}
	}else if(menutype == MENU_TYPE::PAUSA)
	{
		//CONTINUAR
		if(x >= 290 && y >= 220 && x <= 510 && y <= 240 )
		{
			if(!isTest )
				menustate = MENU_STATE::CONTINUAR;
			tx = 290;
			ty = 214;
			bx = 512;
			by = 243;
			ret = true;
		}//REINICIAR
		else if(x >= 306 && y >= 270 && x <= 490 && y <= 290 )
		{
			if(!isTest )
				menustate = MENU_STATE::REINICIAR;
			tx = 306;
			ty = 268;
			bx = 496;
			by = 296;
			ret = true;
		}//MENU
		else if(x >= 346 && y >= 320 && x <= 450 && y <= 340 )
		{
			if(!isTest ){
				menustate = MENU_STATE::MENU;			
				SetMenu(MENU_TYPE::PAUSA);
			}
			tx = 346;
			ty = 320;
			bx = 457;
			by = 348;
			ret = true;
		}
	}
	else if(menutype == MENU_TYPE::PLAY_AGAIN)
	{
		//SI
		if(x >= 330 && y >= 255 && x <= 460 && y <= 220 )
		{
			if(!isTest )
				menustate = MENU_STATE::REINICIAR;
			tx = 330;
			ty = 255;
			bx = 460;
			by = 220;
			ret = true;
		}//NO
		else if(x >= 427 && y >= 255 && x <= 480 && y <= 280 )
		{
			if(!isTest ){
				menustate = MENU_STATE::MENU;			
				SetMenu(MENU_TYPE::GENERAL);
			}
			tx = 427;
			ty = 255;
			bx = 480;
			by = 280;
			ret = true;
		}
	}

	return ret;
}

bool Menu::Hit(int x,int y)
{
	return Test(x,y,false);
}