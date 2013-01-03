#include "GameObject.h"


#ifndef PATO_H
#define PATO_H

class Pato : public GameObject
{
private:
	enum Estado
	{		
		caer=0,
		planear=1,
		morir=2
	};
	Estado estado;
	float angulo;
	float force;
	float time_lastFrame;
	float time_nextPattern;
	float time_CountPattern;
	void Init_Pattern(Estado estado);
	void Update_Pattern(Estado estado);
	void Update_Planear();
	void Update_Caer();
	void Update_Morir();
	void Init_Planear();
	void Init_Caer();
	void Init_Morir();
public:
	void Update(RenderWindow *app);
	bool Hit(Rect<int> *rect) const;
	bool Hit(int x,int y) const;
	void Init(RenderWindow *app);
	float getAngulo();
	float getForce();
	Pato(float angulo,float force);
};

#endif