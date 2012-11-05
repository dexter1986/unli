#include<SFML\Graphics.hpp>
#include<cstring>

#ifndef ENEMIGO_H
#define ENEMIGO_H

class Enemigo
{
private:
	int pos_x,pos_y,max_X,max_Y,width,height;
	sf::Sprite sprite;
	sf::Image mat;	
	void AdjusPosition();
public:
	Enemigo(std::string file,int max_x,int max_y);
	sf::Sprite& Draw();
	bool Hit(int x, int y);
	void Random();
};

#endif