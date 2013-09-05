#include "Prince.h"


Prince::Prince(void):SpriteBase(10,"prince.png")
{
	estado_Actual = Estado::PARADO_I;
	direccion = -1;
	velocidad.x = 22.0f;	
}

Prince::~Prince(void)
{
}

void Prince::InicializarAnimaciones()
{
	animaciones[Estado::PARADO_I].SetLoop(false);
	//<sprite n="1/A00.png" x="2" y="2" w="8" h="41"/>
	animaciones[Estado::PARADO_I].AddFrame(sf::IntRect(2,2,10,43),0.1f);

	animaciones[Estado::GIRO_D].SetLoop(false);
	//<sprite n="1/A00.png" x="2" y="2" w="8" h="41"/>
	animaciones[Estado::GIRO_D].AddFrame(sf::IntRect(2,2,10,43),0.1f);
	//<sprite n="1/A01.png" x="12" y="2" w="9" h="39"/>
	animaciones[Estado::GIRO_D].AddFrame(sf::IntRect(12,2,21,41),0.1f);
    //<sprite n="1/A02.png" x="23" y="2" w="10" h="39"/>
	animaciones[Estado::GIRO_D].AddFrame(sf::IntRect(23,2,33,41),0.1f);
    //<sprite n="1/A03.png" x="35" y="2" w="12" h="40"/>
	animaciones[Estado::GIRO_D].AddFrame(sf::IntRect(35,2,47,42),0.1f);
    //<sprite n="1/A04.png" x="49" y="2" w="15" h="40"/>
	animaciones[Estado::GIRO_D].AddFrame(sf::IntRect(49,2,64,42),0.1f);
    //<sprite n="1/A05.png" x="66" y="2" w="14" h="40"/>
	animaciones[Estado::GIRO_D].AddFrame(sf::IntRect(66,2,80,42),0.1f);
    //<sprite n="1/A06.png" x="82" y="2" w="10" h="40"/>
	animaciones[Estado::GIRO_D].AddFrame(sf::IntRect(82,2,92,42),0.1f);
    //<sprite n="1/A07.png" x="94" y="2" w="11" h="40"/>
	animaciones[Estado::GIRO_D].AddFrame(sf::IntRect(94,2,105,42),0.1f);
	//<sprite n="1/A08.png" x="107" y="2" w="9" h="40"/>
	animaciones[Estado::GIRO_D].AddFrame(sf::IntRect(107,2,116,42),0.1f);

    animaciones[Estado::PARADO_D].SetLoop(false);
	//<sprite n="1/A08.png" x="107" y="2" w="9" h="40"/>
	animaciones[Estado::PARADO_D].AddFrame(sf::IntRect(107,2,116,42),0.1f);

	animaciones[Estado::GIRO_I].SetLoop(false);
	//<sprite n="1/A08.png" x="107" y="2" w="9" h="40"/>
	animaciones[Estado::GIRO_I].AddFrame(sf::IntRect(107,2,116,42),0.1f);
	//<sprite n="1/A07.png" x="94" y="2" w="11" h="40"/>
	animaciones[Estado::GIRO_I].AddFrame(sf::IntRect(94,2,105,42),0.1f);
	//<sprite n="1/A06.png" x="82" y="2" w="10" h="40"/>
	animaciones[Estado::GIRO_I].AddFrame(sf::IntRect(82,2,92,42),0.1f);
	//<sprite n="1/A05.png" x="66" y="2" w="14" h="40"/>
	animaciones[Estado::GIRO_I].AddFrame(sf::IntRect(66,2,80,42),0.1f);
	//<sprite n="1/A04.png" x="49" y="2" w="15" h="40"/>
	animaciones[Estado::GIRO_I].AddFrame(sf::IntRect(49,2,64,42),0.1f);
	 //<sprite n="1/A03.png" x="35" y="2" w="12" h="40"/>
	animaciones[Estado::GIRO_I].AddFrame(sf::IntRect(35,2,47,42),0.1f);
	//<sprite n="1/A02.png" x="23" y="2" w="10" h="39"/>
	animaciones[Estado::GIRO_I].AddFrame(sf::IntRect(23,2,33,41),0.1f);
	//<sprite n="1/A01.png" x="12" y="2" w="9" h="39"/>
	animaciones[Estado::GIRO_I].AddFrame(sf::IntRect(12,2,21,41),0.1f);
	//<sprite n="1/A00.png" x="2" y="2" w="8" h="41"/>
	animaciones[Estado::GIRO_I].AddFrame(sf::IntRect(2,2,10,43),0.1f);


	animaciones[Estado::CORRIENDO_I].SetLoop(true);	
 //  //<sprite n="2/B00.png" x="96" y="140" w="9" h="40"/>
	//animaciones[Estado::CORRIENDO_I].AddFrame(sf::IntRect(96,140,105,180),0.1f);
    
	//<sprite n="2/B01.png" x="107" y="140" w="11" h="40"/>
	//animaciones[Estado::CORRIENDO_I].AddFrame(sf::IntRect(107,140,118,180),0.1f);
    
	//<sprite n="2/B02.png" x="120" y="140" w="13" h="40"/>
	//animaciones[Estado::CORRIENDO_I].AddFrame(sf::IntRect(120,140,133,180),0.1f);
	//<sprite n="2/B03.png" x="135" y="140" w="15" h="39"/>
	animaciones[Estado::CORRIENDO_I].AddFrame(sf::IntRect(135,140,150,179),0.1f);
	//<sprite n="2/B0.png" x="74" y="140" w="20" h="39"/>
	//animaciones[Estado::CORRIENDO_I].AddFrame(sf::IntRect(74,140,94,179),0.1f);
    //<sprite n="2/B05.png" x="152" y="140" w="26" h="39"/>
	animaciones[Estado::CORRIENDO_I].AddFrame(sf::IntRect(152,140,178,179),0.1f);
	//<sprite n="2/B06.png" x="180" y="140" w="24" h="39"/>
	animaciones[Estado::CORRIENDO_I].AddFrame(sf::IntRect(180,140,204,179),0.1f);
    //<sprite n="2/B07.png" x="206" y="140" w="17" h="38"/>
	animaciones[Estado::CORRIENDO_I].AddFrame(sf::IntRect(206,140,223,178),0.1f);
    //<sprite n="2/B08.png" x="225" y="140" w="26" h="39"/>
	animaciones[Estado::CORRIENDO_I].AddFrame(sf::IntRect(225,140,251,179),0.1f);
    //<sprite n="2/B09.png" x="253" y="140" w="26" h="39"/>
	animaciones[Estado::CORRIENDO_I].AddFrame(sf::IntRect(253,140,279,179),0.1f);
    //<sprite n="2/B10.png" x="281" y="140" w="19" h="38"/>
	animaciones[Estado::CORRIENDO_I].AddFrame(sf::IntRect(281,140,300,178),0.1f);	
	

	animaciones[Estado::DETENERSE_I].SetLoop(false);	
	//<sprite n="2/B02.png" x="120" y="140" w="13" h="40"/>
	animaciones[Estado::DETENERSE_I].AddFrame(sf::IntRect(120,140,133,180),0.1f);
	//<sprite n="2/B01.png" x="107" y="140" w="11" h="40"/>
	animaciones[Estado::DETENERSE_I].AddFrame(sf::IntRect(107,140,118,180),0.1f);  
	//<sprite n="2/B00.png" x="96" y="140" w="9" h="40"/>
	animaciones[Estado::DETENERSE_I].AddFrame(sf::IntRect(96,140,105,180),0.1f); 


	animaciones[Estado::CORRIENDO_D].SetLoop(true);	
 //  //<sprite n="2/B00.png" x="96" y="140" w="9" h="40"/>
	//animaciones[Estado::CORRIENDO_D].AddFrame(sf::IntRect(96,140,105,180),0.1f);    
	//<sprite n="2/B01.png" x="107" y="140" w="11" h="40"/>
	//animaciones[Estado::CORRIENDO_D].AddFrame(sf::IntRect(107,140,118,180),0.1f);    
	//<sprite n="2/B02.png" x="120" y="140" w="13" h="40"/>
	//animaciones[Estado::CORRIENDO_D].AddFrame(sf::IntRect(120,140,133,180),0.1f);
	//<sprite n="2/B03.png" x="135" y="140" w="15" h="39"/>
	animaciones[Estado::CORRIENDO_D].AddFrame(sf::IntRect(135,140,150,179),0.1f);
	//<sprite n="2/B0.png" x="74" y="140" w="20" h="39"/>
	//animaciones[Estado::CORRIENDO_D].AddFrame(sf::IntRect(74,140,94,179),0.1f);
    //<sprite n="2/B05.png" x="152" y="140" w="26" h="39"/>
	animaciones[Estado::CORRIENDO_D].AddFrame(sf::IntRect(152,140,178,179),0.1f);
	//<sprite n="2/B06.png" x="180" y="140" w="24" h="39"/>
	animaciones[Estado::CORRIENDO_D].AddFrame(sf::IntRect(180,140,204,179),0.1f);
    //<sprite n="2/B07.png" x="206" y="140" w="17" h="38"/>
	animaciones[Estado::CORRIENDO_D].AddFrame(sf::IntRect(206,140,223,178),0.1f);
    //<sprite n="2/B08.png" x="225" y="140" w="26" h="39"/>
	animaciones[Estado::CORRIENDO_D].AddFrame(sf::IntRect(225,140,251,179),0.1f);
    //<sprite n="2/B09.png" x="253" y="140" w="26" h="39"/>
	animaciones[Estado::CORRIENDO_D].AddFrame(sf::IntRect(253,140,279,179),0.10f);
    //<sprite n="2/B10.png" x="281" y="140" w="19" h="38"/>
	animaciones[Estado::CORRIENDO_D].AddFrame(sf::IntRect(281,140,300,178),0.1f);	
	

	animaciones[Estado::DETENERSE_D].SetLoop(false);	
	//<sprite n="2/B02.png" x="120" y="140" w="13" h="40"/>
	animaciones[Estado::DETENERSE_D].AddFrame(sf::IntRect(120,140,133,180),0.1f);
	//<sprite n="2/B01.png" x="107" y="140" w="11" h="40"/>
	animaciones[Estado::DETENERSE_D].AddFrame(sf::IntRect(107,140,118,180),0.1f);  
	//<sprite n="2/B00.png" x="96" y="140" w="9" h="40"/>
	animaciones[Estado::DETENERSE_D].AddFrame(sf::IntRect(96,140,105,180),0.1f);
  
	
	
	
}

void Prince::Internal_Mover_y_Animar()
{
	switch(estado_Actual)
	{
		case PARADO_I:
			if(joystick.left)
			{
				CambiarEstado(CORRIENDO_I);
				direccion = -1;
			}
			else if(joystick.right)
			{
				CambiarEstado(GIRO_D);
				direccion = 0;
			}
			else if(joystick.a)
			{

			}
			break;
		case GIRO_D:
			if(!AnimationEnded())
				break;
			if(!joystick.right)
			{
				CambiarEstado(PARADO_D);	
				direccion = 0;
			}
			else if(joystick.right)
			{
				CambiarEstado(CORRIENDO_D);	
				direccion = 1;
			}
			else if(joystick.left)
			{
				CambiarEstado(GIRO_I);	
				direccion = 0;
			}
			break;
		case PARADO_D:
			if(joystick.left)
			{
				CambiarEstado(GIRO_I);	
				direccion = 0;
			}
			else if(joystick.right)
			{			
				CambiarEstado(CORRIENDO_D);
				direccion = 1;
			}
			else if(joystick.a)
			{

			}
			break;
		case GIRO_I:
			if(!AnimationEnded())
				break;
			if(!joystick.left)
			{
				CambiarEstado(PARADO_I);
				direccion = 0;
			}
			else if(joystick.left)
			{
				CambiarEstado(CORRIENDO_I);
				direccion = -1;
			}
			else if(joystick.right)
			{
				CambiarEstado(GIRO_D);
				direccion = 0;
			}
			break;
		case CORRIENDO_I:			
			if(!joystick.left)
			{
				CambiarEstado(DETENERSE_I);	

			}			
			else if(joystick.left)
			{
				/*animaciones[Estado::CORRIENDO_I].Reset();
				animaciones[Estado::CORRIENDO_I].SetCurrentFrameNum(3);*/
			}
			else if(joystick.right)
			{

			}
			break;
		case DETENERSE_I:
			if(!AnimationEnded())
				break;
			CambiarEstado(PARADO_I);
			direccion = 0;
			break;
		case CORRIENDO_D:			
			if(!joystick.right)
			{
				CambiarEstado(DETENERSE_D);				
			}						
			else if(joystick.right)
			{
				////La imagen es igual pero reflejada
				//animaciones[Estado::CORRIENDO_D].Reset();
				//animaciones[Estado::CORRIENDO_D].SetCurrentFrameNum(3);				
			}
			else if(joystick.left)
			{
				
			}
			break;
		case DETENERSE_D:
			if(!AnimationEnded())
				break;
			CambiarEstado(PARADO_D);
			direccion = 0;
			break;
	}

	// segun el estado, movemos horizontalmente
	if(estado_Actual==CORRIENDO_I || estado_Actual==CORRIENDO_D){
		//Move(direccion * velocidad.x * dt, 0);
	}
		
	FlipX(direccion>0);	
}