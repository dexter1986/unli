#include "Lista.h"

Lista::Lista(void)
{
	_first = NULL;
	_last = NULL;
	_current = NULL;
	_length = 0;
}

Lista::~Lista(void)
{
	Nodo* n = _first;
	Nodo* aux = NULL;
	while(n != NULL)
	{
		aux = n->_next;
		delete n;
		n = aux;
	}
}

int Lista::GetLength()
{
	return _length;
}

GameObject* Lista::First()
{
	_current = _first;
	if(_first != NULL)
	{	
		return _first->_object;
	}
	return NULL;
}

GameObject* Lista::Last()
{
	_current = _last;
	if(_last != NULL)
	{
		return _last->_object;
	}
	return NULL;
}

GameObject* Lista::Next(void)
{
	if(_current	!= NULL)
	{
		_current = _current->_next;		
		if(_current != NULL)
			return _current->_object;
	}
	return NULL;	
}

bool Lista::IsNext(void)
{
	if(_current != NULL)
		return true;
	return false;
}

GameObject* Lista::Search(int value)
{
	_current = InternalSearch(value);
	if(_current != NULL)
		return _current->_object;
	return NULL;
}

Nodo* Lista::InternalSearch(int value)
{	
	Nodo* n = NULL;
	if(!IsEmpty())
	{
		n = _first;
		while(n->_next != NULL && n->_value != value)
			n = n->_next;
		
		if(n->_value == value)
			return n;
		else
			n = NULL;
	}
	return n;
}

//Agrega un nodo y lo ubica ordenado de menor a mayor
void Lista::Add(int value,GameObject* object)
{
	_length++;
	Nodo* n = new Nodo(value,object);
	
	if(IsEmpty())
	{
		_first = n;
		_last = n;		
		_current = n;
	}
	else
	{
		Nodo* aux = _first;		
		while(aux->_next != NULL && aux->_value < value)
			aux = aux->_next;			
		
		if(aux->_value > value)
		{
			if(aux->_prev != NULL)
			{
				aux->_prev->_next = n;
			}

			n->_prev = aux->_prev;

			n->_next = aux;
			aux->_prev = n;

			if(_first == aux)
				_first = n;
		}
		else
		{
			if(aux->_next != NULL)
			{
				aux->_next->_prev = n;
				n->_next = aux->_next;
			}
			
			aux->_next = n;
			n->_prev =  aux;

			if(_last == aux)
				_last = n;
		}
	}	
}

void Lista::Remove(int value)
{
	Nodo* n = InternalSearch(value);
	if(n != NULL)
	{	
		if(n->_prev != NULL)
			n->_prev->_next = n->_next;			

		if(n->_next != NULL)
			n->_next->_prev = n->_prev;

		if(_first == n)
		{
			_first = n->_next;
			if(_first != NULL)
				_first->_prev = NULL;
		}

		if(_last == n )
		{
			_last = n->_prev;
			if(_last != NULL)
				_last->_next = NULL;
		}

		if(_current == n)
			_current = NULL;

		delete n;
		_length--;
	}
	n = NULL;
}

void Lista::Remove()
{
	Remove(_current->_value);
}

bool Lista::IsEmpty()
{
	if(_first == _last && _first == NULL)
		return true;
	else
		return false;
}


