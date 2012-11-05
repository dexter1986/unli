#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

#ifndef ZONE_H
#define ZONE_H

class Zone
{
private:			
	bool isEnable;	
	Image mat;	
	Sprite zone;
	Rect<float> rect;
public:
	void Enable(bool enable);	
	Zone(int wnd_width,int wnd_height);	
	bool Hit(FloatRect target);
	void Draw(RenderWindow *app);					
};

#endif
