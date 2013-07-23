#pragma once
#include "gameobject.h"
class Vagon :
	public GameObject
{
private:
	int _nro;
	Text text;
	void CenterText();
public:
	Vagon();
	int GetValue();
	void Init();
	void Update();
	void Render(RenderWindow* wnd);
	void CheckCollitions(bool isColl);
	~Vagon(void);
};

