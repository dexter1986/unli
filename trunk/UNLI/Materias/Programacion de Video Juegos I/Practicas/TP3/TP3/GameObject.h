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
	bool _isEnable;
	std::string _textureName;
	Vector2f _position;
public:
	const Drawable& DrawObject();
	bool Enable();	
	void Draw();
	void SetPosition(float x,float y);
	const Vector2f& GetPosition();
	virtual void Init();
	virtual void UpdatePoolEvents(Event& evt); 
	virtual void Update();
	virtual void CheckCollitions();	
	virtual void UpdatePhysics();	
	virtual void Move();	
	GameObject();
	virtual ~GameObject();
};