#ifndef PRINCE_H
#define PRINCE_H

#include "SpriteBase.h"

class Prince :
	public SpriteBase
{
private:

	enum Estado{
		PARADO_D = 0,
		PARADO_I = 1,
		GIRO_D = 2,
		GIRO_I = 3,
		CORRIENDO_D = 4,
		CORRIENDO_I = 5,
		DETENERSE_D = 6,
		DETENERSE_I = 7,
		SALTANDO = 8,
		SALTANDO_Y_MOVIENDOSE = 9,		
	};

protected:	
	// inicializa las animaciones, es llamado en el constructor
	void InicializarAnimaciones();	
	// algunas acciones
	void Saltar();	
	bool ColisionaConSuelo();	
	void Internal_Mover_y_Animar();
public:
	Prince(void);
	~Prince(void);		
};

#endif
