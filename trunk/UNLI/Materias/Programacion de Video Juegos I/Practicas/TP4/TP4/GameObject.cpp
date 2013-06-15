#include "GameObject.h"

GameObject::GameObject()
{
	_isEnable = true;
	_isLeft = false;
	_isRight = false;
}

GameObject::~GameObject()
{

}

bool GameObject::Enable()
{
	return _isEnable;
}

void GameObject::Draw(RenderWindow* wnd)
{

}

void GameObject::Move()
{
	Flip();
	_sprite.setPosition(_position);
}

void GameObject::Init()
{
	_sprite.setTexture(ImageManager::Instance()->getImage(_textureName));
	_sprite.setPosition(_position);
	FloatRect rect = _sprite.getLocalBounds();
	_width = (int)rect.width;
	_height = (int)rect.height;
}

void GameObject::UpdatePoolEvents(Event& evt)
{

}

void GameObject::Update()
{

}

void GameObject::Rotate(float ang)
{
	_sprite.rotate(ang);
}

void GameObject::CheckCollitions(bool isColl)
{

}

const FloatRect& GameObject::GetBound()
{
	return _sprite.getGlobalBounds();
}

bool GameObject::TestCollitions(GameObject& target)
{
	FloatRect rect_t = target.GetBound();
	FloatRect rect = _sprite.getGlobalBounds();
	
	if(rect.intersects(rect_t))
	{
		return true;
	}
	return false;
}

void GameObject::UpdatePhysics()
{

}

void GameObject::CenterOrigin()
{
	float mitadAncho = _width/2.0f;
	float mitadAlto = _height/2.0f;
	_sprite.setOrigin(mitadAncho, mitadAlto);	
}

void GameObject::SetPosition(float x,float y)
{
	_position.x = x;
	_position.y = y;
}

void GameObject::Flip()
{
	bool isLeft = false;
	bool isRight = false;
	Vector2f pos = _sprite.getPosition();
	
	if(_position.x > pos.x)
	{
		isRight = true;
	}
	else if(_position.x < pos.x)
	{
		isLeft = true;
	}

	if(isRight && !_isRight)
	{
		//flip right
		_sprite.setTextureRect(sf::IntRect(_width, 0,-_width,_height));
		_isRight = true;
		_isLeft = false;
	}
	else if(isLeft && !_isLeft)
	{
		//flip left
		_sprite.setTextureRect(sf::IntRect(0, 0, _width, _height));
		_isRight = false;
		_isLeft = true;
	}
}

const Vector2f& GameObject::GetPosition()
{
	return _position;
}

void GameObject::Size(float factorX, float factorY)
{
	_sprite.setScale(factorX,factorY);
	FloatRect rect = _sprite.getLocalBounds();
	_width = (int)rect.width;
	_height = (int)rect.height;
}

const Drawable& GameObject::DrawObject()
{
	return _sprite;
}
