#include "EfectoParticulas.h"


EfectoParticulas::EfectoParticulas(float x, float y,float z, float _aceleracionY, float _aceleracionX,
	int _tamano, int _cantidad, int _vida, float _velocidad,
	int _amplitud, int _direccion):
		posicionX(x), posicionY(y), posicionZ(z), aceleracionY(_aceleracionY), tamano(_tamano),
		cantidad(_cantidad), vida(_vida), velocidad(_velocidad), amplitud(_amplitud),
		direccion(_direccion),aceleracionX(_aceleracionX)

{	

	dt = 1.0f;
	r = 0.6f;
	g = 0.2f;
	b = 0.0f;
	
	activo = false;
	
	particulas = new Particula[cantidad];
	
	tipoEfecto = EfectoParticulasConfig::EfectoParticulasTypeFX::Propulsion;

	for(int i=0; i < cantidad ; ++i)
		particulas[i].Inicializar(posicionX, posicionY, velocidad, r, g, b, amplitud, direccion, vida);
}

void EfectoParticulas::Actualizar()
{
	// actualizamos las particulas
	for (int i=0; i<cantidad ; i++)
	{		
		// si esta muerta y sigue activo el efecto entonces la volvemos a lanzar
		if( particulas[i].life<=0 && activo )
			particulas[i].Inicializar(posicionX, posicionY, velocidad, r, g, b, amplitud, direccion, vida);
		
		// actualizamos la particula
		particulas[i].red   = r;  //se asignan los colores de la particula que se dibujara luego
		particulas[i].green = g;
		particulas[i].blue  = b;	
		
		particulas[i].x    += particulas[i].vX * dt; //la particula avanza
		particulas[i].y    += particulas[i].vY * dt;		
		particulas[i].vX   += aceleracionX; //aceleracion horizontal cero
		particulas[i].vY   -= aceleracionY; //aceleracion vertical configurable				
		
		particulas[i].life -= 1; //decrementa la vida =>la particula se extingue, al decrementarse el alpha
		//cout << "particles[i].life: " << particles[i].life << endl;
	}
}

void EfectoParticulas::Dibujar()
{
	if(activo)
	{
		glPushMatrix();
		//// dibujamos el origen del efecto de particulas
		//glPointSize(tamano/2);
		//glBegin(GL_POINTS);
		//glVertex2f(posicionX,posicionY);
		//glEnd();
		//
		// dibujamos las particulas

		glTranslated(0,0,posicionZ);
		glEnable(GL_BLEND);
		int tam = tamano*Escala;
		glPointSize(tam);
		glBegin(GL_POINTS);
		for(int i=0; i<cantidad ; i++)
		{	
			glColor4f(particulas[i].red, particulas[i].green, particulas[i].blue, (float(particulas[i].life)/particulas[i].life_initial));				
		
			switch(tipoEfecto)
			{
				case EfectoParticulasConfig::EfectoParticulasTypeFX::Propulsion:
					glVertex2f(particulas[i].x, particulas[i].y);
					glVertex2f(particulas[i].x+2, particulas[i].y+2);
					glVertex2f(particulas[i].x-2, particulas[i].y-2);
					glVertex2f(particulas[i].x+2, particulas[i].y-2);
					glVertex2f(particulas[i].x-2, particulas[i].y+2);
					break;
				case EfectoParticulasConfig::EfectoParticulasTypeFX::HuellaVehiculo:
					glVertex2f(particulas[i].x+2, particulas[i].y+2);										
					glVertex2f(particulas[i].x-2, particulas[i].y-2);
					glVertex2f(particulas[i].x, particulas[i].y);
				
					break;
				case EfectoParticulasConfig::EfectoParticulasTypeFX::Incendio:
					break;
			}
		}
		glEnd();
		glDisable(GL_BLEND);
		glPopMatrix();
	}
}

void EfectoParticulas::ToggleActivo()
{
	activo = !activo;
}

bool EfectoParticulas::GetActivo()
{
	return activo;
}
	
void EfectoParticulas::SetPosicion(float x, float y)
{
	posicionX = x;
	posicionY = y;
}

float EfectoParticulas::GetAceleracionY()
{
	return aceleracionY;
}

void EfectoParticulas::SetAceleracionY(float _aceleracionY)
{
	aceleracionY = _aceleracionY;
}

int EfectoParticulas::GetCantidad()
{
	return cantidad;
}

void EfectoParticulas::SetCantidad(int _cantidad)
{
	cantidad = _cantidad;
	delete[] particulas;
	particulas = new Particula[cantidad];
	for(int i=0; i < cantidad ; ++i)
		particulas[i].Inicializar(posicionX, posicionY, velocidad, r, g, b, amplitud, direccion, vida);
}

int EfectoParticulas::GetTamano()
{
	return tamano;
}

void EfectoParticulas::SetTamano(int _tamano)
{
	tamano = _tamano;
}

int EfectoParticulas::GetVida()
{
	return vida;
}

void EfectoParticulas::SetVida(int _vida)
{
	vida = _vida;
}

float EfectoParticulas::GetVelocidad()
{
	return velocidad;
}

void EfectoParticulas::SetVelocidad(float _velocidad)
{
	velocidad = _velocidad;
}

int EfectoParticulas::GetAmplitud()
{
	return amplitud;
}

void EfectoParticulas::SetAmplitud(int _amplitud)
{
	amplitud = _amplitud;
}

int EfectoParticulas::GetDireccion()
{
	return direccion;
}

void EfectoParticulas::SetDireccion(int _direccion)
{
	direccion = _direccion;
}

void EfectoParticulas::SetDeltaTiempo(float _dt)
{
	dt = _dt;
}
		
void EfectoParticulas::SetColor(float _r, float _g, float _b)
{
	r = _r;
	g = _g;
	b = _b;
}
