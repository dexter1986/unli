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

bool GameObject::Hit(int x,int y)
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

void GameObject::Draw(RenderWindow *app)
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

GameObject::~GameObject(void)
{

}
