#include "GameObject.h"

#ifndef MENU_H
#define MENU_H

class Menu : public GameObject
{	
public:
	typedef enum _MENU_TYPE_
	{
		GENERAL=0,
		PAUSA=1,
		PLAY_AGAIN=2,
		M_AYUDA=3,
		M_CREDITOS=4,
	}MENU_TYPE;

	typedef enum _MENU_STATE_
	{
		JUGAR=0,
		AYUDA=1,
		CREDITOS=2,
		SALIR=3,
		CONTINUAR=4,
		REINICIAR=5,
		MENU=6
	}MENU_STATE;

private:
	float tx;
	float ty;
	float bx; 
	float by;
	MENU_TYPE menutype;
	MENU_STATE menustate;	
public:
	Menu();
	void SetMenu(MENU_TYPE type); 
	void Update(RenderWindow *app);
	void Draw(RenderWindow *app);
	void Init(RenderWindow *app);	
	bool Test(int x,int y,bool isTest=true);
	bool Hit(int x,int y);
	MENU_STATE GetState();
};

#endif