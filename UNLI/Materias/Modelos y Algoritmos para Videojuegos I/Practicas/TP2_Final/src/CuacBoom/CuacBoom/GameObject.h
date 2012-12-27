#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class GameObject
{
protected:		
	Vector2f pos;	
	float width,height;
	bool isEnable;
	bool isCollide;
	Image img;
	Sprite sprite;
	void LoadSprite(const std::string &Filename);		
public:
	GameObject();
	GameObject(bool isCollide,const std::string &Filename);	
	virtual void Enable(bool enable);
	virtual void Draw(RenderWindow *app);
	virtual bool Hit(int x,int y);
	virtual void Update(RenderWindow *app);
	const sf::Image *ShareImage();
	virtual void Move(float x,float y);
	~GameObject(void);
};

#endif