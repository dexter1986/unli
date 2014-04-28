#include "Hormiga.h"
#include "HormigaStates.h"
#include "utils.h"

#include "Tablero.h"

Hormiga::Hormiga(Tablero* tab):tablero(tab)
{
	//cargamos los recursos de SFML
	m_img.loadFromFile("hormigas.png");
	m_spr.setTexture(m_img);
	m_spr.setScale(0.2f,0.2f);
	m_spr.setOrigin(m_img.getSize().x / 2.0f, m_img.getSize().y / 2.0f);

	m_text.setFont(tablero->m_fuente);
	m_text.setCharacterSize(15);

	SetPosition(Utils::GetRandomVec(0.0f, 600.0f, 0.0f, 600.0f));

	//creamos la maquina de estados
	m_pStateMachine= new StateMachine<Hormiga>(this);
	//configuramos el estado inicial
	m_pStateMachine->SetCurrentState(State_Hormiga_Deambular::Instance());
	
}

Tablero* Hormiga::GetTablero(){
	return tablero;
}

StateMachine<Hormiga>* Hormiga::GetFSM() const{
	return m_pStateMachine;
}

Hormiga::~Hormiga(void)
{
}

void Hormiga::SetTarget(Comida* c){
	p_target = c;
}

Comida* Hormiga::GetTarget(){
	return p_target;
}

void Hormiga::Draw(RenderWindow *wnd){
	wnd->draw(m_spr);
	wnd->draw(m_text);
}

void Hormiga::Update(){
	m_pStateMachine->Update();		
	m_text.setString(m_pStateMachine->CurrentState()->GetStateName());
	m_text.setOrigin(m_img.getSize().x / 2.0f, m_img.getSize().y / 2.0f);
}

void Hormiga::SetPosition(Vector2f pos){
	m_spr.setPosition(pos);
	Vector2f post= pos;
	post.y-=20;	
	m_text.setPosition(post);
}

Vector2f Hormiga::GetPosition(){
	return m_spr.getPosition();
}

void Hormiga::ChangeDirection(){

	dir = Utils::GetRandomVec(-1.0f, 1.0f, -1.0f, 1.0f);
	float norm= sqrt(dir.x*dir.x+dir.y*dir.y);
	dir.x /=norm;
	dir.y /=norm;
}

void Hormiga::Move(){

	Vector2f posActual= m_spr.getPosition();
	posActual.x+= dir.x * HORMIGAVEL;
	posActual.y+= dir.y * HORMIGAVEL;
	SetPosition(posActual);
}

void Hormiga::Evade(Matador *m)
{
	Vector2f posActual = m_spr.getPosition();
	Vector2f posTarget = m->GetPosition();
	dir = posTarget - posActual;

	//Invierte el vector
	dir.x *= -1;
	dir.y *= -1;
		
	float norm = sqrt(dir.x*dir.x + dir.y*dir.y);
	dir.x /= norm; 
	dir.y /= norm;
}

void Hormiga::Chase()
{
	Vector2f posActual = m_spr.getPosition();
	Vector2f posTarget = p_target->GetPosition();
	dir = posTarget - posActual;
	float norm = sqrt(dir.x*dir.x + dir.y*dir.y);
	dir.x /= norm;
	dir.y /= norm;
}

