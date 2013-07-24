#pragma once
#include "Nodo.h"

class Lista
{
private:
	int _length;
	Nodo* _first;
	Nodo* _last;
	Nodo* _current;
	Nodo* InternalSearch(int value);	
public:
	int GetLength();
	GameObject* First(void);
	GameObject* Last(void);
	GameObject* Next(void);
	GameObject* Search(int value);	
	void Add(int value, GameObject* object);	
	void Remove(int value);
	void Remove();
	bool IsEmpty(void);
	bool IsNext(void);
	Lista(void);
	~Lista(void);
};

