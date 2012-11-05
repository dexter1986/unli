#include"Enemigo.h"
#include<ctime>

Enemigo::Enemigo(std::string file,int max_x,int max_y)
{	
	max_X = max_x;
	max_Y = max_y;

	pos_x =  rand()%max_x;
	pos_y =  rand()%max_y;

	mat.LoadFromFile(file);

	sprite.SetImage(mat);
	
	width = sprite.GetSize().x;
	height = sprite.GetSize().y;
	
	AdjusPosition();
	sprite.SetPosition(pos_x,pos_y);
}

sf::Sprite& Enemigo::Draw()
{
	return sprite;
}

bool Enemigo::Hit(int x, int y)
{
	if(pos_x < x && pos_x + width > x && pos_y < y && pos_y + height > y)
		return true;

	return false;
}

void Enemigo::Random()
{
	pos_x =  rand()%max_X;
	pos_y =  rand()%max_Y;
	AdjusPosition();
	sprite.SetPosition(pos_x,pos_y);
}

void Enemigo::AdjusPosition()
{
	if(pos_x + width > max_X)
		pos_x -= width;

	if(pos_y + height > max_Y)
		pos_y -= height;
}