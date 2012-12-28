#include <SFML/Graphics.hpp>
#include "GameObjectBase.h"

using namespace sf;
using namespace std;

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class GameObject: public GameObjectBase
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
	void Enable(bool enable);
	void Init(RenderWindow *app);
	void Draw(RenderWindow *app) const;
	bool Hit(int x,int y) const;
	Vector2f GetPos() const;
	float GetWidth() const;
	float GetHeight() const;
	void Update(RenderWindow *app);
	const sf::Image *ShareImage();
	void Move(float x,float y);
	void Rotate(float rad);
	void SetCenter(float x,float y);
	~GameObject(void);
};

#endif