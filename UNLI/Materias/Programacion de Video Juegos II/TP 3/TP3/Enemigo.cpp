#include "Enemigo.h"


Enemigo::Enemigo(void)
{
	isNPC = true;	
	contadorPasos = 0;
	contadorDisparos = 0;
	currentState = EstadosFSM::DETENIDO;
	currentModo = ModoComportamiento::MERCENARIO;
}

Enemigo::~Enemigo(void)
{

}

void Enemigo::AiTracker(Personaje *p)
{
	target = p;
}

void Enemigo::Inicializar(ManejadorDisparos *d,Nivel *n)
{
	Personaje::Inicializar(d,n);		
	SetPosition(256,32);	
	SetupComportamiento();
}

void Enemigo::SetupComportamiento()
{
	switch(currentModo)
	{
	case GUARDIA:
		SetColor(Color::Red);
		break;
	case PATRULLA:
		SetColor(Color::Green);
		break;
	case MERCENARIO:
		SetColor(Color::Blue);
		break;
	}
	
}

void Enemigo::AiNpc()
{
	switch(currentModo)
	{
	case GUARDIA:
		ModoGuardia();
		break;
	case PATRULLA:
		ModoPatrulla();
		break;
	case MERCENARIO:
		ModoMercenario();
		break;
	}
}

void Enemigo::ModoGuardia()
{
	if(currentState == DETENIDO)
	{
		int opcion = rand()%3;
						
		switch(opcion)
		{
		case 0:
			currentState = GIRAR;
			break;		
		case 2:
			currentState = BUSCAR;
			break;
		}
		contadorPasos = rand()%100+100;
	}
	else if(currentState == BUSCAR)
	{
		bool isTargetInRange =  CheckTargetVisibility();

		if(isTargetInRange)
		{
			currentState = DISPARAR;	
			contadorDisparos = rand()%50+50;
			contadorPasos += rand()%50+50;
		}
	}
	else if(currentState == GIRAR)
	{
		if(direccion == LEFT)
		{
			joystick.right  = true;
		}
		else
		{
			joystick.left  = true;
		}
		currentState = NOP;
	}	
	else if(currentState == DISPARAR)
	{
		if(contadorDisparos > 0)
		{
			joystick.a = true;
			joystick.down = true;
			contadorDisparos--;
		}
		else
		{
			currentState = NOP;
		}

	}

	if(contadorPasos <= 0)
	{
		currentState = DETENIDO;
	}else
	{
		contadorPasos--;
	}
}

void Enemigo::ModoPatrulla()
{
	if(currentState == DETENIDO)
	{
		int opcion = rand()%3;
		
		switch(opcion)
		{
		case 0:
			currentState = GIRAR;
			break;
		case 1:
			currentState = CORRER;		
			break;
		case 2:
			currentState = BUSCAR;
			break;
		}
		contadorPasos = rand()%100+100;
	}
	else if(currentState == BUSCAR)
	{
		bool isTargetInRange =  CheckTargetVisibility();

		if(isTargetInRange)
		{
			currentState = DISPARAR;	
			contadorDisparos = rand()%10+10;
			contadorPasos += rand()%50+50;
		}
	}
	else if(currentState == GIRAR)
	{
		if(direccion == LEFT)
		{
			joystick.right  = true;
		}
		else
		{
			joystick.left  = true;
		}
		currentState = NOP;
	}
	else if(currentState == CORRER)
	{
		bool isTargetInRange =  CheckTargetVisibility();
			
		if(isTargetInRange)
		{
			currentState = DETENIDO;
		}

		if(isHitWall)
		{
			currentState = GIRAR;
		}
		if(direccion == LEFT)
		{
			joystick.left = true;
		}
		else
		{
			joystick.right = true;
		}
	}
	else if(currentState == DISPARAR)
	{
		if(contadorDisparos > 0)
		{
			joystick.a = true;
			contadorDisparos--;
		}
	}

	if(contadorPasos <= 0)
	{
		currentState = DETENIDO;
	}else
	{
		contadorPasos--;
	}
}

void Enemigo::ModoMercenario()
{
	if(currentState == DETENIDO)
	{
		currentState = BUSCAR;
		contadorPasos = rand()%20+20;
	}
	else if(currentState == BUSCAR)
	{
		bool isTargetInRange =  CheckTargetVisibility();

		if(isTargetInRange)
		{
			int opcion = rand()%3;

			switch(opcion)
			{
			case 0:
				currentState = CORRER;
				break;
			case 1:
				currentState = DISPARAR;
				break;
			case 2:
				currentState = CORRER_Y_DISPARAR;
				break;
			}				
			contadorDisparos = rand()%5+5;
			contadorPasos += rand()%10+10;
		}
	}
	else if(currentState == GIRAR)
	{
		if(direccion == LEFT)
		{
			joystick.right  = true;
		}
		else
		{
			joystick.left  = true;
		}
		currentState = DETENIDO;
	}
	else if(currentState == CORRER)
	{
		if(isHitWall)
		{
			currentState = GIRAR;
		}
		if(direccion == LEFT)
		{
			joystick.left = true;
		}
		else
		{
			joystick.right = true;
		}
	}	
	else if(currentState == DISPARAR)
	{	
		if(contadorDisparos > 0)
		{
			joystick.a = true;
			contadorDisparos--;
		}		
	}
	else if(currentState == CORRER_Y_DISPARAR)
	{
		if(direccion == LEFT)
		{
			joystick.left = true;
		}
		else
		{
			joystick.right = true;
		}
		if(contadorDisparos > 0)
		{
			joystick.a = true;
			contadorDisparos--;
		}
	}

	if(contadorPasos <= 0)
	{
		currentState = DETENIDO;
	}else
	{
		contadorPasos--;
	}
}

bool Enemigo::CheckTargetVisibility()
{
	return true;
}

