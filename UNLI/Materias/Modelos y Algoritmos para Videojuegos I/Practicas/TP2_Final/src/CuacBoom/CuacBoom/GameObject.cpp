#include "GameObject.h"
#include "Helper.h"

GameObject::GameObject(bool isCollide,const std::string &filename)
{
	GameObject::isCollide = isCollide;
	GameObject::isEnable = false;
	GameObject::maxframes = 0;
	GameObject::currentframe = 0;
	GameObject::LoadSprite(filename);
}

GameObject::GameObject(bool isCollide,const std::string &filename,int frames)
{
	GameObject::isCollide = isCollide;
	GameObject::isEnable = false;
	GameObject::maxframes = frames;
	GameObject::currentframe = 0;
	GameObject::LoadSprite(filename,frames);
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

bool GameObject::isAnim() const
{
	return maxframes > 1;
}

void GameObject::LoadSprite(const std::string &filename)
{
	img.LoadFromFile(filename);
	sprite.SetImage(img);
	width =  sprite.GetSize().x;
	height = sprite.GetSize().y;
}

void GameObject::LoadSprite(const std::string &filename,int frames)
{
	imgAnim = new Image[frames];

	int pos = filename.find_last_of(".");
	
	string extension = filename.substr(pos);
	string name =  filename.substr(0,pos);
	string file;

	for(int i=0;i<frames;i++)
	{		
		file = name + "-" + Helper::ToInt(i) + extension;
		
		(imgAnim+i)->LoadFromFile(file);
	}

	sprite.SetImage(*(imgAnim+currentframe));
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
	/*if(maxframes > 0)
	{
		delete imgAnim;		
	}*/
}

void GameObject::Anim()
{

}

void GameObject::UpdateFrame()
{
	sprite.SetImage(*(imgAnim+currentframe));
}
