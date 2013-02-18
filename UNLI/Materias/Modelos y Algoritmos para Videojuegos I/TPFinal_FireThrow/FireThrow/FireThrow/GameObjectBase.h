#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

#ifndef GAME_OBJECT_BASE_H
#define GAME_OBJECT_BASE_H

class GameObjectBase
{
	virtual void Enable(bool enable) = 0;
	virtual void Draw(RenderWindow *app) const = 0;
	virtual bool Hit(int x,int y) const = 0;
	virtual void Update(RenderWindow *app) = 0;	
	virtual void Init(RenderWindow *app) = 0;
	virtual void Move(float x,float y) = 0;
};

#endif