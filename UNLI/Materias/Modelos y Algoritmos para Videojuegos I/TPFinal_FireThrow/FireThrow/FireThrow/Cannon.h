#include <SFML/Graphics.hpp>
#include "GameObjectBase.h"
#include "GameObject.h"

using namespace sf;
using namespace std;

#ifndef CANNON_H
#define CANNON_H

class Cannon : public GameObjectBase
{
private:
	GameObject *base;
	GameObject *cano;
	float rot_rad;
	int vidas;
	float velocidad;
	float angulo;
	void Init(RenderWindow *app);
public:
	void SetVelocidad(float value);
	void SetAngulo(float value);
	float GetVelocidad();
	float GetAngulo();
	int GetVidas();
	void SetVidas(int value);
	float GetRad() const;
	Vector2f GetPosCano() const;
	Vector2f GetPos() const;
	Vector2f GetSize() const;
	Vector2f GetLargoCano() const;
	void Enable(bool enable);
	void Draw(RenderWindow *app) const;	
	bool Hit(int x,int y) const;
	void Update(RenderWindow *app);	
	
	void Init(RenderWindow *app,Vector2f *pos);
	void Move(float x,float y);
	void Rotate(float rad);
	Cannon();
	~Cannon();
};

#endif