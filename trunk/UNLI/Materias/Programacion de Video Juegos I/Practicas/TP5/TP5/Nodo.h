#pragma once
#include "GameObject.h"

class Nodo
{
private:
	GameObject* _object;	
	Nodo* _next;
	Nodo* _prev;
	int _value;
	friend class Lista;
public:	
	Nodo(int value, GameObject* object);
	~Nodo(void);
};

