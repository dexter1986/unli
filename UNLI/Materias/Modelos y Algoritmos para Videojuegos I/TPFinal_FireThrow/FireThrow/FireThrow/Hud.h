#include "GameObject.h"


#ifndef HUD_H
#define HUD_H

#define MAX_FX_TIME 2

class Hud : public GameObject
{
public:
	typedef struct PlayerState_
	{
		string nombre;
		float angulo;
		float velocidad;
		int puntos;
	}PlayerState;
private:
	float tx;
	float ty;
	float bx; 
	float by;

	Font font;
	sf::String text;

	int cantjugadores;
	int puntos;

	string cantPuntos;
	string nomplayer1;
	string nomplayer2;

	int estado;
	float windForce;

	bool isCleanPlayer1;
	bool isCleanPlayer2;
	bool isCleanPuntos;
	bool isTurnoPlayer1;
	bool isSetVel;
	bool isSetAng;

	void SeleccionJugadores(RenderWindow *app);
	void NombreJugadores(RenderWindow *app);
	void HudUser(RenderWindow *app);
	
	PlayerState playerstate[2];
	float initFXTime;
public:
	void SetStatePlayer1(float angulo,float velocidad,int puntos);
	void SetStatePlayer2(float angulo,float velocidad,int puntos);
	int GetVidas();
	int GetCantJugadores();
	void SetIsVel();
	void SetIsAng();
	void SetIsFire();
	void ProcessEvent(Event &evt);
	bool Hit(int x,int y);
	bool Test(int x,int y);
	void Draw(RenderWindow *app);
	void Init(RenderWindow *app);
	void SetTurno(bool isPlayer1);
	void SetWind(float value);
	int GetState();
	void InitLevel();
	void ShowGano(RenderWindow *app,bool isPlayer1);
	bool ShowLostVida(RenderWindow *app,bool isPlayer1);
	void InitFXTime();
	Hud();
};

#endif
