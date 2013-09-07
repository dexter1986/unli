#ifndef PRINCE_H
#define PRINCE_H

#include "SpriteBase.h"

class Prince :
	public SpriteBase
{
private:
	float vx;
	float vy;
	enum Estado{
		PARADO=0,
		CAMINAR,
		AGARRARSE,
		GIRAR,
		GIRO,		
		PARAR,
		PASO,
		SALTO,
		SALTAR,
		SUBIR,
		TREPAR
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
