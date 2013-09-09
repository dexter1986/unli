#include "Prince.h"


Prince::Prince(void):SpriteBase(14,"prince.png")
{
	estado_Actual = Estado::PARADO;
	//Derecha 1, izquierda -1
	direccion = 1;
	velocidad.x = 42.0f;	
}

Prince::~Prince(void)
{
}

void Prince::InicializarAnimaciones()
{
	//<sprite n="v5.png" x="350" y="224" w="10" h="40"/>
	animaciones[Estado::PARADO].AddFrame(350,224,10,40,0.1);
	
	animaciones[Estado::GIRO].SetLoop(false);
	
	//<sprite n="v0.png" x="268" y="224" w="10" h="39"/>
    animaciones[Estado::GIRO].AddFrame(268,224,10,39,0.1);
	//<sprite n="v1.png" x="280" y="224" w="14" h="40"/>
	animaciones[Estado::GIRO].AddFrame(280,224,14,40,0.1);
	//<sprite n="v2.png" x="296" y="224" w="18" h="40"/>
	animaciones[Estado::GIRO].AddFrame(296,224,18,40,0.1);
	//<sprite n="v3.png" x="316" y="224" w="18" h="39"/>
	animaciones[Estado::GIRO].AddFrame(316,224,18,39,0.1);
	//<sprite n="v4.png" x="336" y="224" w="12" h="39"/>
	animaciones[Estado::GIRO].AddFrame(336,224,12,39,0.1);	
	//<sprite n="v5.png" x="350" y="224" w="10" h="40"/>
	animaciones[Estado::GIRO].AddFrame(350,224,10,40,0.1);

	animaciones[Estado::CAMINAR].SetLoop(false);
	
	//<sprite n="c00.png" x="263" y="2" w="13" h="40"/>
	animaciones[Estado::CAMINAR].AddFrame(263,2,13,40,0.1);
    //<sprite n="c01.png" x="278" y="2" w="16" h="40"/>
	animaciones[Estado::CAMINAR].AddFrame(278,2,16,40,0.1);
    //<sprite n="c02.png" x="296" y="2" w="18" h="40"/>
	animaciones[Estado::CAMINAR].AddFrame(296,2,18,40,0.1);
    //<sprite n="c03.png" x="316" y="2" w="24" h="39"/>
	animaciones[Estado::CAMINAR].AddFrame(316,2,24,39,0.1);
    //<sprite n="c04.png" x="342" y="2" w="23" h="38"/>
	animaciones[Estado::CAMINAR].AddFrame(342,2,23,38,0.1);
    //<sprite n="c05.png" x="367" y="2" w="23" h="39"/>
	animaciones[Estado::CAMINAR].AddFrame(367,2,23,39,0.1);
    //<sprite n="c06.png" x="392" y="2" w="31" h="39"/>
	animaciones[Estado::CAMINAR].AddFrame(392,2,31,39,0.1);
    //<sprite n="c07.png" x="425" y="2" w="31" h="40"/>
	animaciones[Estado::CAMINAR].AddFrame(425,2,31,40,0.1);
    //<sprite n="c08.png" x="458" y="2" w="23" h="39"/>
	animaciones[Estado::CAMINAR].AddFrame(458,2,23,39,0.1);
    //<sprite n="c09.png" x="483" y="2" w="24" h="38"/>
	animaciones[Estado::CAMINAR].AddFrame(483,2,24,38,0.1);
    //<sprite n="c10.png" x="2" y="49" w="29" h="39"/>
	animaciones[Estado::CAMINAR].AddFrame(2,49,29,39,0.1);
    //<sprite n="c11.png" x="33" y="49" w="31" h="40"/>
	animaciones[Estado::CAMINAR].AddFrame(33,49,31,40,0.1);
    //<sprite n="c12.png" x="66" y="49" w="21" h="38"/>
	animaciones[Estado::CAMINAR].AddFrame(66,49,21,38,0.1);
    //<sprite n="c13.png" x="89" y="49" w="23" h="39"/>
	animaciones[Estado::CAMINAR].AddFrame(89,49,23,39,0.1);

	//<sprite n="lc0.png" x="450" y="49" w="29" h="39"/>
		animaciones[Estado::CAMINAR].AddFrame(450,49,29,39,0.1);
    //<sprite n="lc1.png" x="2" y="91" w="31" h="40"/>
		animaciones[Estado::CAMINAR].AddFrame(2,91,31,40,0.1);
    //<sprite n="lc2.png" x="35" y="91" w="21" h="38"/>
		animaciones[Estado::CAMINAR].AddFrame(35,91,21,38,0.1);
    //<sprite n="lc3.png" x="58" y="91" w="23" h="39"/>
		animaciones[Estado::CAMINAR].AddFrame(58,91,23,39,0.1);
    //<sprite n="lc4.png" x="83" y="91" w="31" h="39"/>
		animaciones[Estado::CAMINAR].AddFrame(83,91,31,39,0.1);
    //<sprite n="lc5.png" x="116" y="91" w="31" h="40"/>
		animaciones[Estado::CAMINAR].AddFrame(116,91,31,40,0.1);
    //<sprite n="lc6.png" x="149" y="91" w="23" h="39"/>
		animaciones[Estado::CAMINAR].AddFrame(149,91,23,39,0.1);
    //<sprite n="lc7.png" x="174" y="91" w="23" h="38"/>
		animaciones[Estado::CAMINAR].AddFrame(174,91,23,38,0.1);


	animaciones[Estado::PARAR].SetLoop(false);
		
	//<sprite n="p0.png" x="199" y="91" w="27" h="40"/>
    animaciones[Estado::PARAR].AddFrame(199,91,27,40,0.1);
	//<sprite n="p1.png" x="228" y="91" w="20" h="39"/>
	animaciones[Estado::PARAR].AddFrame(228,91,20,39,0.1);
    //<sprite n="p2.png" x="250" y="91" w="37" h="39"/>
	animaciones[Estado::PARAR].AddFrame(250,91,37,39,0.1);
    //<sprite n="p3.png" x="289" y="91" w="27" h="38"/>
	animaciones[Estado::PARAR].AddFrame(289,91,27,38,0.1);
    //<sprite n="p4.png" x="318" y="91" w="18" h="39"/>
	animaciones[Estado::PARAR].AddFrame(318,91,18,39,0.1);
    //<sprite n="p5.png" x="338" y="91" w="12" h="39"/>
	animaciones[Estado::PARAR].AddFrame(338,91,12,39,0.1);


	animaciones[Estado::PASO].SetLoop(false);

	//<sprite n="pa0.png" x="352" y="91" w="11" h="40"/>
		 animaciones[Estado::PASO].AddFrame(352,90,11,40,0.1);
    //<sprite n="pa1.png" x="365" y="91" w="11" h="39"/>
		 animaciones[Estado::PASO].AddFrame(365,90,11,40,0.1);
    //<sprite n="pa2.png" x="378" y="91" w="16" h="38"/>
		 animaciones[Estado::PASO].AddFrame(378,90,16,40,0.1);
    //<sprite n="pa3.png" x="396" y="91" w="24" h="37"/>
		 animaciones[Estado::PASO].AddFrame(396,90,24,40,0.1);
    //<sprite n="pa4.png" x="422" y="91" w="26" h="37"/>
		 animaciones[Estado::PASO].AddFrame(422,90,26,40,0.1);
    //<sprite n="pa5.png" x="450" y="91" w="16" h="39"/>
		 animaciones[Estado::PASO].AddFrame(450,90,16,40,0.1);
    //<sprite n="pa6.png" x="468" y="91" w="11" h="40"/>
		 animaciones[Estado::PASO].AddFrame(468,90,11,40,0.1);
    //<sprite n="pa7.png" x="481" y="91" w="10" h="40"/>
		 animaciones[Estado::PASO].AddFrame(481,90,10,40,0.1);

	animaciones[Estado::SALTO].SetLoop(false);

	//<sprite n="sa00.png" x="347" y="133" w="14" h="40"/>
		 animaciones[Estado::SALTO].AddFrame(347,133,14,40,0.1);
    //<sprite n="sa01.png" x="363" y="133" w="20" h="39"/>
		animaciones[Estado::SALTO].AddFrame(363,133,20,40,0.1);
    //<sprite n="sa02.png" x="385" y="133" w="27" h="31"/>
		animaciones[Estado::SALTO].AddFrame(385,133,27,40,0.1);
    //<sprite n="sa03.png" x="414" y="133" w="27" h="31"/>
		animaciones[Estado::SALTO].AddFrame(414,133,27,40,0.1);
    //<sprite n="sa04.png" x="443" y="133" w="24" h="32"/>
		animaciones[Estado::SALTO].AddFrame(443,133,24,40,0.1);
    //<sprite n="sa05.png" x="469" y="133" w="36" h="34"/>
		animaciones[Estado::SALTO].AddFrame(469,133,36,40,0.1);
    //<sprite n="sa06.png" x="2" y="178" w="47" h="32"/>
		animaciones[Estado::SALTO].AddFrame(2,178,47,40,0.1);
    //<sprite n="sa07.png" x="51" y="178" w="48" h="28"/>
		animaciones[Estado::SALTO].AddFrame(51,178,48,40,0.1);
    //<sprite n="sa08.png" x="101" y="178" w="38" h="27"/>
		animaciones[Estado::SALTO].AddFrame(101,178,38,40,0.1);
    //<sprite n="sa09.png" x="141" y="178" w="30" h="26"/>
		animaciones[Estado::SALTO].AddFrame(141,178,30,40,0.1);
    //<sprite n="sa10.png" x="173" y="178" w="20" h="24"/>
		animaciones[Estado::SALTO].AddFrame(173,178,20,40,0.1);
    //<sprite n="sa11.png" x="195" y="178" w="24" h="29"/>
		animaciones[Estado::SALTO].AddFrame(195,178,24,38,0.1);
    //<sprite n="sa12.png" x="221" y="178" w="20" h="32"/>
		animaciones[Estado::SALTO].AddFrame(221,178,20,38,0.1);
    //<sprite n="sa13.png" x="243" y="178" w="15" h="39"/>
		animaciones[Estado::SALTO].AddFrame(243,178,15,38,0.1);
    //<sprite n="sa14.png" x="260" y="178" w="11" h="39"/>
		animaciones[Estado::SALTO].AddFrame(260,178,11,38,0.1);

	animaciones[Estado::GIRAR].SetLoop(false);

	//<sprite n="g00.png" x="114" y="49" w="27" h="40"/>
		animaciones[Estado::GIRAR].AddFrame(114,49,27,40,0.1);
	//<sprite n="g01.png" x="143" y="49" w="20" h="39"/>
		animaciones[Estado::GIRAR].AddFrame(143,49,20,40,0.1);
    //<sprite n="g02.png" x="165" y="49" w="37" h="39"/>
		animaciones[Estado::GIRAR].AddFrame(165,49,37,40,0.1);
    //<sprite n="g03.png" x="204" y="49" w="27" h="38"/>
		animaciones[Estado::GIRAR].AddFrame(204,49,27,40,0.1);
    //<sprite n="g04.png" x="233" y="49" w="27" h="37"/>
		animaciones[Estado::GIRAR].AddFrame(233,49,27,40,0.1);
    //<sprite n="g05.png" x="262" y="49" w="31" h="37"/>
		animaciones[Estado::GIRAR].AddFrame(262,49,31,40,0.1);
    //<sprite n="g06.png" x="295" y="49" w="28" h="32"/>
		animaciones[Estado::GIRAR].AddFrame(295,49,28,40,0.1);
    //<sprite n="g07.png" x="325" y="49" w="33" h="35"/>
		animaciones[Estado::GIRAR].AddFrame(325,49,33,35,0.1);
    //<sprite n="g08.png" x="360" y="49" w="28" h="36"/>
		animaciones[Estado::GIRAR].AddFrame(360,49,28,40,0.1);
    //<sprite n="g09.png" x="390" y="49" w="29" h="37"/>
		animaciones[Estado::GIRAR].AddFrame(390,49,29,40,0.1);
    //<sprite n="g10.png" x="421" y="49" w="27" h="36"/>
		animaciones[Estado::GIRAR].AddFrame(421,49,27,40,0.1);

		animaciones[Estado::SALTAR].SetLoop(false);

	//<sprite n="s0.png" x="2" y="130" w="24" h="37"/>
		animaciones[Estado::SALTAR].AddFrame(2,132,24,43,0.1);
    //<sprite n="s1.png" x="28" y="130" w="36" h="38"/>
		animaciones[Estado::SALTAR].AddFrame(28,132,36,43,0.1);
    //<sprite n="s2.png" x="66" y="130" w="14" h="40"/>
		animaciones[Estado::SALTAR].AddFrame(66,132,14,43,0.1);
    //<sprite n="s3.png" x="82" y="130" w="32" h="43"/>
		animaciones[Estado::SALTAR].AddFrame(82,132,32,43,0.1);
    //<sprite n="s4.png" x="116" y="130" w="42" h="39"/>
		animaciones[Estado::SALTAR].AddFrame(116,132,42,43,0.1);
    //<sprite n="s5.png" x="160" y="130" w="47" h="26"/>
		animaciones[Estado::SALTAR].AddFrame(160,132,47,43,0.1);
    //<sprite n="s6.png" x="209" y="130" w="38" h="24"/>
		animaciones[Estado::SALTAR].AddFrame(209,132,38,43,0.1);
    //<sprite n="s7.png" x="249" y="130" w="40" h="34"/>
		animaciones[Estado::SALTAR].AddFrame(249,132,40,43,0.1);
    //<sprite n="s8.png" x="291" y="130" w="29" h="32"/>
		animaciones[Estado::SALTAR].AddFrame(291,132,29,43,0.1);
    //<sprite n="s9.png" x="322" y="130" w="23" h="39"/>
		animaciones[Estado::SALTAR].AddFrame(322,132,23,43,0.1);

		animaciones[Estado::TREPAR].SetLoop(false);

		//<sprite n="t00.png" x="68" y="220" w="9" h="40"/>
			animaciones[Estado::TREPAR].AddFrame(58,224,10,48,0.1);
		//<sprite n="t01.png" x="79" y="224" w="10" h="40"/>
			animaciones[Estado::TREPAR].AddFrame(68,224,10,48,0.1);
		//<sprite n="t02.png" x="91" y="224" w="17" h="39"/>
			animaciones[Estado::TREPAR].AddFrame(79,224,10,48,0.1);
		//<sprite n="t03.png" x="110" y="224" w="20" h="39"/>
			animaciones[Estado::TREPAR].AddFrame(110,224,20,48,0.1);
		//<sprite n="t04.png" x="132" y="224" w="18" h="37"/>
			animaciones[Estado::TREPAR].AddFrame(132,224,18,48,0.1);
		//<sprite n="t05.png" x="152" y="224" w="15" h="35"/>
			animaciones[Estado::TREPAR].AddFrame(152,224,15,48,0.1);
		//<sprite n="t06.png" x="169" y="224" w="21" h="32"/>
			animaciones[Estado::TREPAR].AddFrame(169,224,15,48,0.1);
		
		animaciones[Estado::TREPANDO].SetLoop(false);
		//<sprite n="t07.png" x="192" y="224" w="15" h="38"/>
			animaciones[Estado::TREPANDO].AddFrame(192,218,15,48,0.1);
		//<sprite n="t08.png" x="209" y="224" w="14" h="47"/>
			animaciones[Estado::TREPANDO].AddFrame(209,218,14,48,0.1);
		//<sprite n="t09.png" x="225" y="224" w="17" h="48"/>
			animaciones[Estado::TREPANDO].AddFrame(225,218,17,48,0.1);		

			animaciones[Estado::BAJANDOTREPAR].SetLoop(false);
		//<sprite n="t10.png" x="244" y="224" w="10" h="40"/>
			animaciones[Estado::BAJANDOTREPAR].AddFrame(244,224,10,48,0.1);
		//<sprite n="t11.png" x="256" y="224" w="10" h="40"/>
			animaciones[Estado::BAJANDOTREPAR].AddFrame(256,224,10,48,0.1);
			
			animaciones[Estado::AGARRARSE].SetLoop(true);

			//<sprite n="a00.png" x="2" y="2" w="10" h="45"/>
				 animaciones[Estado::AGARRARSE].AddFrame(2,3,10,45,0.1);
			//<sprite n="a01.png" x="14" y="2" w="16" h="43"/>
				animaciones[Estado::AGARRARSE].AddFrame(14,3,16,43,0.1);
			//<sprite n="a02.png" x="32" y="2" w="19" h="41"/>
				animaciones[Estado::AGARRARSE].AddFrame(32,3,19,41,0.1);
			//<sprite n="a03.png" x="53" y="2" w="16" h="43"/>
				animaciones[Estado::AGARRARSE].AddFrame(53,3,16,43,0.1);
			//<sprite n="a04.png" x="71" y="2" w="10" h="45"/>
				animaciones[Estado::AGARRARSE].AddFrame(71,3,10,45,0.1);
			//<sprite n="a05.png" x="83" y="2" w="16" h="44"/>
				animaciones[Estado::AGARRARSE].AddFrame(83,3,16,44,0.1);
			//<sprite n="a06.png" x="101" y="2" w="23" h="41"/>
				animaciones[Estado::AGARRARSE].AddFrame(101,3,23,41,0.1);
			//<sprite n="a07.png" x="126" y="2" w="26" h="40"/>
				animaciones[Estado::AGARRARSE].AddFrame(126,3,26,40,0.1);
			//<sprite n="a08.png" x="154" y="2" w="24" h="38"/>
				animaciones[Estado::AGARRARSE].AddFrame(154,3,24,38,0.1);
			//<sprite n="a09.png" x="180" y="2" w="26" h="40"/>
				animaciones[Estado::AGARRARSE].AddFrame(180,3,26,40,0.1);
			//<sprite n="a10.png" x="208" y="2" w="23" h="41"/>
				animaciones[Estado::AGARRARSE].AddFrame(208,3,23,41,0.1);
			//<sprite n="a11.png" x="233" y="2" w="16" h="44"/>
				animaciones[Estado::AGARRARSE].AddFrame(233,3,16,44,0.1);
			//<sprite n="a12.png" x="251" y="2" w="10" h="45"/>
				animaciones[Estado::AGARRARSE].AddFrame(251,3,10,45,0.1);

}



void Prince::Internal_Mover_y_Animar()
{
	switch(estado_Actual)
	{
		case PARADO:
			if(joystick.left && direccion == 1)
			{
				CambiarEstado(GIRO);
				direccion = -1;
			}
			else if(joystick.left && direccion == -1)
			{
				CambiarEstado(CAMINAR);
				vx = velocidad.x;
			}
			else if(joystick.right && direccion == -1)
			{
				CambiarEstado(GIRO);
				direccion = 1;
			}
			else if(joystick.right && direccion == 1)
			{
				CambiarEstado(CAMINAR);
				vx = velocidad.x;
			}
			else if(joystick.b)
			{
				CambiarEstado(SALTO);
				vx = velocidad.x;				
			}
			else if(joystick.a)
			{
				CambiarEstado(PASO);
				vx = velocidad.x / 2;
			}
			else if(joystick.up)
			{
				CambiarEstado(TREPAR);	
				vx = -5.0 * direccion;
				vy = 0;
			}
			break;		
		case GIRO:
			 if(!AnimationEnded())
			 {
				 break;
			 }			 
			 CambiarEstado(PARADO);			
			break;	
		case CAMINAR:			
			
			if(!joystick.right && joystick.left && direccion == 1)
			{
				CambiarEstado(GIRAR);
			}
			else if(!joystick.left && joystick.right && direccion == -1)
			{
				CambiarEstado(GIRAR);
			}
			else if((!joystick.left  && direccion == -1) || (!joystick.right && direccion == 1))
			{
				CambiarEstado(PARAR);
				vx = velocidad.x;
			}
			else if(joystick.b)
			{
				CambiarEstado(SALTAR);					
			}
			
			if(!AnimationEnded())
			{
				break;
			}
			animaciones[Estado::CAMINAR].Reset();
			animaciones[Estado::CAMINAR].SetCurrentFrameNum(15);			
			break;
		case PARAR:
			if(AnimationEnded())
			{
				CambiarEstado(PARADO);
			}
			break;
		case PASO:
			if(AnimationEnded())
			{
				CambiarEstado(PARADO);
			}
			break;
		case SALTO:						
			if(AnimationEnded())	
			{
				CambiarEstado(PARADO);
			}
			break;
		case GIRAR:
			if(AnimationEnded())	
			{
				CambiarEstado(CAMINAR);
				if(direccion == 1)
					direccion = -1;
				else
					direccion  = 1;
				animaciones[Estado::CAMINAR].Reset();
				animaciones[Estado::CAMINAR].SetCurrentFrameNum(15);
			}
			break;
		case SALTAR:
			if(AnimationEnded())	
			{
				CambiarEstado(CAMINAR);
				animaciones[Estado::CAMINAR].Reset();
				animaciones[Estado::CAMINAR].SetCurrentFrameNum(15);
			}
			break;
		case TREPAR:
			if(AnimationEnded())	
			{
				Saltar();
				CambiarEstado(TREPANDO);
			}
			break;
		case TREPANDO:	
			if(joystick.a)
			{
				CambiarEstado(AGARRARSE);
			}
			else if(ColisionaConSuelo())
			{	
				CambiarEstado(BAJANDOTREPAR);				
			}
			break;
		case BAJANDOTREPAR:
			if(AnimationEnded())
			{	
				CambiarEstado(PARADO);
			}			
			break;
		case AGARRARSE:
			if(!joystick.a)
			{	
				CambiarEstado(TREPANDO);
				animaciones[Estado::TREPANDO].SetCurrentFrameNum(2);
				AnimationStop();				
			}
			break;
	}

	// segun el estado, movemos horizontalmente
	if(estado_Actual ==  CAMINAR || (estado_Actual == PARAR && direccion == 1) || estado_Actual == PASO || estado_Actual == SALTO
		|| estado_Actual == SALTAR ||  estado_Actual == TREPAR){		
		Move(direccion * vx * dt, 0);		
	}
	else if(estado_Actual == PARAR && direccion == -1){
		vx -= 2.0f;
		if(vx < 0)
			vx = 0;
		Move(direccion * vx * dt, 0);		
	}

	// segun el estado, movemos verticalmente
	if(estado_Actual == TREPANDO){		
		vy+=gravity*dt;
		Move(0, vy*dt);		
	}	
		
	FlipX(direccion<0);	
}

void Prince::Saltar(){
	vy=v0;	
	posicion.y=GetPosition().y;
}

// detecta si hubo colision con el suelo y ajusta la coordenada y del sprite
bool Prince::ColisionaConSuelo(){
	if(GetPosition().y >= posicion.y){
		// si hubo colision con el suelo, puede haber ocurrido
		// interpenetracion, por lo que es necesario ajustar
		// la coordenada y a la del suelo que guardamos antes
		SetY(posicion.y);
		return true;
	}else{
		return false;
	}
}