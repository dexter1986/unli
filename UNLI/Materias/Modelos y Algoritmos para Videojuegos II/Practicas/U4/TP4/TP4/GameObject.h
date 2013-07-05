#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "imageManager.h"
#include "PhysicManager.h"

using namespace sf;
using namespace std;

class GameObject
{
private: 	
	Sprite _sprite;	   	

protected:
	//cuerpo de box2d 
	b2Body* _controlBody;
	b2Fixture* _fixture;

	bool _isLeft;
	bool _isRight;
	int _width;
	int _height;
	bool _isEnable;
	bool _isInitPhysic;
	std::string _textureName;
	Vector2f _position;
public:
	bool _isNoFlip;
	bool _isManualFlip;
	void ManualFlip();
	const FloatRect& GetBound();
	virtual const Drawable& DrawObject();
	bool Enable();	
	void Disable();	
	virtual void Draw(RenderWindow* wnd);
	void SetPosition(float x,float y);
	const Vector2f& GetPosition();
	virtual void InitPhysic();
	virtual void Init();
	virtual void UpdatePoolEvents(Event& evt); 
	virtual void Update();
	virtual void CheckCollitions(bool isColl);
	virtual bool TestCollitions(GameObject& target);	
	virtual void UpdatePhysics();
	virtual void CenterOrigin();
	virtual void Rotate(float ang);
	virtual void Flip();	
	virtual void Size(float factorX, float factorY);	
	virtual void Move();	
	GameObject();
	virtual ~GameObject();
};