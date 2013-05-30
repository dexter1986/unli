#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
#include "Box2DHelper.h"

using namespace sf;
using namespace std;

class GameObject
{
private: 
	bool isEnable;
	Sprite _sprite;
	b2Body* body;
	std::string textureName;   
protected:
	virtual const Drawable& DrawObject()=0;
public:
	bool Enable();	
	void Draw();
	virtual void Init();
	virtual void UpdatePoolEvents(Event evt)=0; 
	virtual void Update();
	virtual void CheckCollitions();	
	virtual void UpdatePhysics();	
	GameObject();
	virtual ~GameObject();
};