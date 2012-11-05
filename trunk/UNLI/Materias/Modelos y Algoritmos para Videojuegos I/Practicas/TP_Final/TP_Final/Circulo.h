#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

#ifndef CIRCULO_H
#define CIRCULO_H

class Circulo
{
private:
	float time_frec,time_count;
	Vector2f pos[4];
	int index_pos;
	int width,height;
	bool isEnable;
	Image img;
	Sprite sprite;	
	void ResetTime();
	void NexPos();
public:
	void Enable(bool enable);	
	Circulo(int wnd_width,int wnd_height);	
	void Draw(RenderWindow *app);
	bool Hit(int x,int y);
	void Update(RenderWindow *app);
};

#endif