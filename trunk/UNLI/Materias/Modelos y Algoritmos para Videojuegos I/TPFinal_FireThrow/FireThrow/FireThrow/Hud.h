#include "GameObject.h"


#ifndef HUD_H
#define HUD_H

class Hud : public GameObject
{
public:
	typedef struct PlayerState_
	{
		string nombre;
		int angulo;
		int velocidad;
		int puntos;
	}PlayerState;
private:
	int tx;
	int ty;
	int bx; 
	int by;

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

public:
	void SetStatePlayer1(int angulo,int velocidad,int puntos);
	void SetStatePlayer2(int angulo,int velocidad,int puntos);
	int GetVidas();
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
	Hud();
};

#endif
