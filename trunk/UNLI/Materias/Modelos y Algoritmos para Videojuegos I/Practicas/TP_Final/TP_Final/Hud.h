#include <SFML/Graphics.hpp>
#include<cstring>
#include<iostream>
#include<sstream>

using namespace sf;
using namespace std;

#ifndef HUD_H
#define HUD_H

class Hud
{
private:		
	int width,height,vidas_count,puntos_count;
	bool isEnable;
	Image mat_vida;
	Font font;
	Sprite spr_vida;
	String str_vidas;
	String str_puntos;
public:
	void Enable(bool enable);	
	Hud(int wnd_width,int wnd_height);	
	void Draw(RenderWindow *app);		
	void UpdateVidas(int vidas);
	void UpdatePuntos(int puntos);
};

#endif