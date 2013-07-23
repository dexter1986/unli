#include "Nodo.h"

Nodo::Nodo(int value,GameObject* object)
{	
	_object = object; 
	_value = value;
	_prev = NULL;
	_next = NULL;
}

Nodo::~Nodo(void)
{
	delete _object;
}
