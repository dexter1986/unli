#pragma once
#include "gameobject.h"
class Bloque :
	public GameObject
{
private:
	int _nro;
	int _index;
	Text text;
	void CenterText();
public:
	Bloque(int nro,int index);
	void Draw(RenderWindow* wnd);
	void SetNro(int nro,bool isOk);
	int GetIndex();	
	void Init();
	void CheckCollitions(bool isColl);
	~Bloque(void);
};

