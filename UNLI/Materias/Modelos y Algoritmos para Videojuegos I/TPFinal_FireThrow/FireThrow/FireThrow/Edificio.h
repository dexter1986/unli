#include "GameObject.h"

#ifndef EDIFICIO_H
#define EDIFICIO_H

class Edificio : public GameObject
{
private:	
	static const int mx_w = 8;
	static const int mx_h = 7;
	typedef struct Bloque_def
	{
		float pos_x;
		float pos_y;
		bool isActive;		
		Sprite sprite;
	}Bloque;
	/*
	cada bloque tiene 100x80
	Siendo la definicion 800x600
	*/
	Vector2f bloque_size;
	Bloque bloques[mx_w][mx_h];
	bool isInit;
	Vector2f blink_bloque;
	bool isBlink;
	bool blink_fx;
	float blinkTime;
	void Builder(int width,int height);
	void Make();
public:
	Edificio();
	Vector2f* GetPos(bool isPalyer1);
	bool Hit(Vector2f pos);
	void Update(RenderWindow *app);
	void Draw(RenderWindow *app);
	void Init(RenderWindow *app);	
};

#endif