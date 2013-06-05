#include "GameObject.h"

GameObject::GameObject()
{
	_isEnable = true;
}

GameObject::~GameObject()
{

}

bool GameObject::Enable()
{
	return _isEnable;
}

void GameObject::Draw()
{

}

void GameObject::Move()
{
	_sprite.setPosition(_position);
}

void GameObject::Init()
{
	_sprite.setTexture(ImageManager::Instance()->getImage(_textureName));
	_sprite.setPosition(_position);
}

void GameObject::UpdatePoolEvents(Event& evt)
{

}

void GameObject::Update()
{

}

void GameObject::CheckCollitions()
{

}

void GameObject::UpdatePhysics()
{

}

void GameObject::SetPosition(float x,float y)
{
	_position.x = x;
	_position.y = y;
}

const Vector2f& GameObject::GetPosition()
{
	return _position;
}

const Drawable& GameObject::DrawObject()
{
	return _sprite;
}
