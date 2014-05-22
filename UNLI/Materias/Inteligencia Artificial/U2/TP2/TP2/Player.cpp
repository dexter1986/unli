#include "Player.h"


Player::Player(const b2BodyDef& CuerpoDef, const b2FixtureDef& AdornoDef, float escala, sf::Texture* pTextura) : Vehiculo(CuerpoDef, AdornoDef, escala, pTextura)
{
}

void Player::Actualizar(float dt)
{
	EntidadEscena::Actualizar(dt);

	float maxVel = 60.0f;
	float maxAngVel = 4.0f;

	float forward = 1.0f;
	float lateral = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		forward = -1.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		forward = 0.0f;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		lateral = -1.0f;		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		lateral = 1.0f;		
	}	
		
	b2Transform t = m_pCuerpo->GetTransform();	
	b2Vec2 f = b2Vec2(0, 0);
	
	b2Vec2 linVel = m_pCuerpo->GetLinearVelocity();

	float vel = linVel.Length();
	if (forward == 0)
	{
		if (vel > 1)
		{
			f.x = linVel.x / vel > 0 ? 1 : -1;
			vel-=0.5;
		}
	}
	else
	{
		f.x = forward;
		vel = maxVel;
	}

	b2Vec2 dir = b2Mul(t.q, f);
	dir *= vel;

	m_pCuerpo->SetLinearVelocity(dir);

	float angVel = m_pCuerpo->GetAngularVelocity();

	if (lateral == 0)
	{
		if (angVel > 0.1)
		{	
			angVel -= 0.05;
		}
		else if (angVel < -0.1)
		{
			angVel+=0.05;
		}
		else
		{
			angVel = 0;
		}
	}
	else
	{
		angVel = lateral * maxAngVel / 3.14f;
	}

	m_pCuerpo->SetAngularVelocity(angVel);
}
