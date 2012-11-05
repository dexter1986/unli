#include <SFML/Graphics.hpp>
#include<cstring>
#include<iostream>
#include<sstream>

using namespace sf;
using namespace std;

#ifndef LETRA_H
#define LETRA_H

class Letra
{
private:			
	int width,height;
	float pos_x,pos_y;
	bool isEnable;	
	Font font;	
	String str_letra;
	string letra;	
	float velocidad;
	float count;
	float ciclo;
	float iter_max;
	void RndLetter();
public:
	void Reset();
	void Enable(bool enable);	
	bool Enable();
	Letra(int wnd_width,int wnd_height,float iter);	
	void Draw(RenderWindow *app);		
	void Update(RenderWindow *app);	
	FloatRect GetRect();
	bool Compare(char a);
};

#endif