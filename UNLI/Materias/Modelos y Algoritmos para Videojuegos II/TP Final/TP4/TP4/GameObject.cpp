#include "GameObject.h"

GameObject::GameObject()
{
	_isEnable = true;
	_isLeft = false;
	_isRight = false;
	_isNoFlip = false;
	_isManualFlip = false;
	_controlBody = NULL;
	_fixture =  NULL;
	_isInitPhysic = false;
}

GameObject::~GameObject()
{
	if(_isInitPhysic && _controlBody != NULL)
	{
		_controlBody->DestroyFixture(_fixture);
		_fixture = NULL;
		PhysicManager::Instance()->DestroyBody(_controlBody);
		_controlBody = NULL;
	}
}

void GameObject::Disable()
{
	_isEnable = false;
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
	if(!_isManualFlip)
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

void GameObject::InitPhysic()
{	
	_isInitPhysic = true;

	_fixture = &_controlBody->GetFixtureList()[0];

	CenterOrigin();

	SetPosition(_controlBody->GetPosition().x,_controlBody->GetPosition().y);
	_sprite.setPosition(_position);

	float m_angAux = _controlBody->GetAngle();
	_sprite.setRotation(m_angAux*180/3.14f);
		
	b2PolygonShape* box= (b2PolygonShape*) _fixture->GetShape();
	b2AABB boxAABB;
	box->ComputeAABB(&boxAABB,b2Transform_identity);
	
	float sizeBx=2*boxAABB.GetExtents().x;
	float sizeBy=2*boxAABB.GetExtents().y;

	float scaleX= sizeBx/_width;
	float scaleY= sizeBy/_height;

	_sprite.setScale(scaleX,scaleY);
	
	_controlBody->SetUserData(this);
}

void GameObject::UpdatePoolEvents(Event& evt)
{

}

void GameObject::Update()
{
	
}

b2Body* GameObject::GetBody()
{
	return _controlBody;
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
	rect_t.height -= 15.0f;
	rect_t.width -= 15.0f;
	rect_t.top += 15.0f;
	rect_t.left += 15.0f;

	FloatRect rect = _sprite.getGlobalBounds();
	rect.height -= 15.0f;
	rect.width -= 15.0f;
	rect.top += 15.0f;
	rect.left += 15.0f;

	if(rect.intersects(rect_t))
	{
		return true;
	}
	return false;
}

void GameObject::UpdatePhysics()
{
	if(_isInitPhysic && _controlBody != NULL)
	{
		b2Vec2 pos = _controlBody->GetPosition();
		SetPosition(pos.x,pos.y);
		_sprite.setRotation(_controlBody->GetAngle()*180/3.14f);
		_sprite.setPosition(_position);
	}
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

void GameObject::ManualFlip()
{
	if(_isRight)
		_sprite.setTextureRect(sf::IntRect(_width, 0,-_width,_height));
	else if(_isLeft)
		_sprite.setTextureRect(sf::IntRect(0, 0, _width, _height));
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
