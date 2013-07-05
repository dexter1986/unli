#pragma once
#include <Box2D\Box2D.h>
class QueryDisparos: public b2QueryCallback {

private:
	

public:
	b2Vec2 mousePos;
	//Este m�todo se llamar� una vez por cada fixture que
	//est� en colisi�n con el rect�ngulo
	bool ReportFixture(b2Fixture* fixture){
	
		//siempre le aplicamos un impulso en el eje x para poder controlarlo hacia 
		//los costados
		b2Vec2 dir;
		dir.y=0;
		dir.x = (fixture->GetBody()->GetWorldCenter().x - mousePos.x)*20;
		fixture->GetBody()->ApplyLinearImpulse(dir,fixture->GetBody()->GetWorldCenter());		

		//luego le aplicamos una fuerza hacia arriba en el punto d�nde se encuentra
		//el mouse para lograr la rotaci�n del objeto como producto del
		//torque que le generamos
		fixture->GetBody()->ApplyLinearImpulse(b2Vec2(0.0,-50.0),mousePos);		
		
		return true;
	}
	QueryDisparos()
	{
	}
	QueryDisparos(float x, float y)
	{
		mousePos.x = x;
		mousePos.y = y;
	}

};