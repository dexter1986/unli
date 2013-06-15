#include "Bloque.h"
#include "Constantes.h"

Bloque::Bloque(int nro,int index):GameObject()
{
	_textureName = "bloque_pared.png";
	_position.y = 330;
	_nro = nro;
	_index = index;
	text.setColor(Color::Yellow);
	text.setFont(ImageManager::Instance()->GetFont());		
	std::string str= C::NumberToString<int>(nro);
	text.setString(str);
}

Bloque::~Bloque(void)
{

}

void Bloque::Init()
{
	GameObject::Init();
	CenterText();
}

void Bloque::CenterText()
{
	FloatRect rect = text.getLocalBounds();
	text.setPosition(_position.x + (_width - rect.width)/2.0f - rect.left ,_position.y + (_height - rect.height)/2.0f - rect.top);
}

void Bloque::Draw(RenderWindow* wnd)
{
	wnd->draw(text);
}

void Bloque::SetNro(int nro,bool isOk)
{
	_nro = nro;
	std::string str= C::NumberToString<int>(nro);
	text.setString(str);
	if(isOk)
		text.setColor(Color::Green);
	else
		text.setColor(Color::Red);
	CenterText();
}

int Bloque::GetIndex()
{
	return _index;
}

void Bloque::CheckCollitions(bool isColl)
{
	if(isColl)
		text.setColor(Color::Green);
}

