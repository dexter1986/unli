#pragma once
#include "StateMachine.h"
#include "Drawable.h"
#include "Hormiga.h"

#define MATADORVEL 0.2f
class Tablero;
class Hormiga;

class Matador: public DrawBase, public UpdateBase
{

	StateMachine<Matador>* m_pStateMachine;
	Texture m_img;
	Sprite m_spr;
	
	Text m_text;
	Vector2f dir;

	Hormiga* p_target;

public:	
	Tablero* tablero;

	StateMachine<Matador>* GetFSM()const;

	void Draw(RenderWindow* wnd);
	void Update();
	void SetPosition(Vector2f pos);
	Vector2f GetPosition();
	void ChangeDirection();
	void Move();
	void SetTarget(Hormiga* h);
	Hormiga* GetTarget();
	void Chase();
	Tablero* GetTablero();	
	Matador(Tablero* tab);
	~Matador(void);
};

