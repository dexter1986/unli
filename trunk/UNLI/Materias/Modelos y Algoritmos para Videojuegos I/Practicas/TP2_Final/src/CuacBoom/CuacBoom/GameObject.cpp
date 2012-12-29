#include "GameObject.h"

GameObject::GameObject(bool isCollide,const std::string &filename)
{
	GameObject::isCollide = isCollide;
	GameObject::isEnable = false;
	GameObject::LoadSprite(filename);
}

GameObject::GameObject(){
}

void GameObject::Enable(bool enable)
{
	isEnable = enable;
}

const sf::Image *GameObject::ShareImage()
{
	return &img;
}

void GameObject::LoadSprite(const std::string &filename)
{
	img.LoadFromFile(filename);
	sprite.SetImage(img);
	width =  sprite.GetSize().x;
	height = sprite.GetSize().y;
}

bool GameObject::Hit(int x,int y) const
{
	if(!isEnable || !isCollide)
		return false;

	if(pos.x < x && pos.x + width > x && pos.y < y && pos.y + height > y)
	{	
		return true;
	}
	return false;
}

void GameObject::Update(RenderWindow *app)
{}

void GameObject::Draw(RenderWindow *app) const
{
	if(isEnable)
		app->Draw(sprite);
}

void GameObject::Move(float x,float y)
{
	pos.x = x;
	pos.y = y;
	sprite.SetPosition(pos);
}

Vector2f GameObject::GetPos() const
{
	return pos;
}

float GameObject::GetWidth() const
{
	return width;
}

float GameObject::GetHeight() const
{
	return height;
}

void GameObject::Init(RenderWindow *app)
{
}

void GameObject::Rotate(float rad)
{
	sprite.SetRotation(rad);
}

void GameObject::SetCenter(float x,float y)
{
	sprite.SetCenter(x,y);
}

bool GameObject::Hit(Rect<int> *rect) const
{	
	return  rect->Intersects(sprite.GetSubRect());
}

GameObject::~GameObject(void)
{

}
