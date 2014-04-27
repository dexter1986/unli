#include "Comida.h"
#include "utils.h"

Comida::Comida(void)
{
	m_img.loadFromFile("comida.png");
	m_spr.setTexture(m_img);
	m_spr.setScale(0.2f,0.2f);
	m_spr.setOrigin(m_img.getSize().x / 2.0f, m_img.getSize().y / 2.0f);
	SetPosition(Utils::GetRandomVec(0.0f, 600.0f, 0.0f, 600.0f));
	
}

Comida::~Comida(void)
{

}

void Comida::Draw(RenderWindow* wnd){
	
	wnd->draw(m_spr);
}

void Comida::SetPosition(Vector2f pos){

	m_spr.setPosition(pos);
	

}

Vector2f Comida::GetPosition(){
	return m_spr.getPosition();
}