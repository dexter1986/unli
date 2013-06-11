#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "imageManager.h"

using namespace sf;
using namespace std;

class GameObject
{
private: 	
	Sprite _sprite;	   	
protected:
	bool _isLeft;
	bool _isRight;
	int _width;
	int _height;
	bool _isEnable;
	std::string _textureName;
	Vector2f _position;
public:
	const FloatRect& GetBound();
	const Drawable& DrawObject();
	bool Enable();	
	virtual void Draw(RenderWindow* wnd);
	void SetPosition(float x,float y);
	const Vector2f& GetPosition();
	virtual void Init();
	virtual void UpdatePoolEvents(Event& evt); 
	virtual void Update();
	virtual void CheckCollitions(bool isColl);
	virtual bool TestCollitions(GameObject& target);	
	virtual void UpdatePhysics();
	virtual void CenterOrigin();
	virtual void Rotate(float ang);
	virtual void Flip();	
	virtual void Move();	
	GameObject();
	virtual ~GameObject();
};