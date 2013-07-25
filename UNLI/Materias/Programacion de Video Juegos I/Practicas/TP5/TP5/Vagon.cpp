#include "Vagon.h"
#include "Constantes.h"

Vagon::Vagon():GameObject()
{
	_textureName = "vagon.png";
	_position.y = 52.0f;
	_position.x = 100.0f;
	_nro = rand()%99+1;	
	text.setColor(Color::Yellow);
	text.setFont(ImageManager::Instance()->GetFont());		
	text.setCharacterSize(28);
	std::string str= C::NumberToString<int>(_nro);
	text.setString(str);
	_isManualFlip = true;
}

Vagon::~Vagon(void)
{

}

void Vagon::SetValue(int value)
{	
	_nro = value;
	if(_nro == -1)
		text.setString("");
	else
	{
		std::string str= C::NumberToString<int>(_nro);
		text.setString(str);
	}
}

void Vagon::Update()
{
	Move();
	CenterText();
}

void Vagon::Init()
{
	GameObject::Init();	
	CenterText();
}

int Vagon::GetValue()
{
	return _nro;
}

void Vagon::CenterText()
{
	FloatRect rect = text.getLocalBounds();
	text.setPosition(_position.x + (_width - rect.width)/2.0f - rect.left ,_position.y + (_height - rect.height)/2.0f - rect.top);
}

void Vagon::Render(RenderWindow* wnd)
{
	wnd->draw(DrawObject());
	wnd->draw(text);
}

void Vagon::CheckCollitions(bool isColl)
{

}

