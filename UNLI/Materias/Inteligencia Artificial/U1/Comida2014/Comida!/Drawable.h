#pragma once
#include "stdafx.h"
using namespace sf;

class DrawBase{


public:

	virtual void Draw(RenderWindow* wnd)=0;


};

class UpdateBase{


public:

	virtual void Update()=0;
};