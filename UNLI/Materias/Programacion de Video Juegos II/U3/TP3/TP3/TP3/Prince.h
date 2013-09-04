#ifndef PRINCE_H
#define PRINCE_H

#include "SpriteBase.h"

class Prince :
	public SpriteBase
{
private:

	enum Estado{
		PARADO = 0,
		CORRIENDO = 1,		
		SALTANDO = 2,
		SALTANDO_Y_MOVIENDOSE = 3,		
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
