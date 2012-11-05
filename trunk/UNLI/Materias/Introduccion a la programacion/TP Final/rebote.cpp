#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cmath>
#include<ctime>
#include<conio.h>
#include<conio2.h>

using namespace std;

	

int main(int argc,char *argv[])
{
	const char KEY_ESC   = 27;
	const char KEY_LEFT  = 75;
	const char KEY_RIGHT = 77;
	const int FPS = 30;
	const int AUTO_DEF = 25;
	
	//resolucion video:
	//80 Columnas
	//25 filas
	const char CLEAR = ' ';
	const int  BARRA_ANCHO = 10;
	const char BARRA_FILL = '§';	
	const char BALL_FILL = 'O';
	const int  TARGET_ANCHO = 10;
	const char TARGET_FILL = '';	
	const int  LIMIT_LOW_X = 1;
	const int  LIMIT_LOW_Y = 1;
	const int  LIMIT_HIGH_X = 80;
	const int  LIMIT_HIGH_Y = 25;
	
	const int TARGET_X = 35;
	const int TARGET_Y = 5;
	
	const int VEL_X = 3;
	const int VEL_Y = 2;
	
	//Control de colision para el puntaje.
	int TARGET_FLAG_1 = false;
	int TARGET_FLAG_2 = false;
	int TARGET_FLAG_3 = false;
	int TARGET_FLAG_4 = false;
	int TARGET_FLAG_5 = false;
	int TARGET_FLAG_6 = false;
	int TARGET_FLAG_7 = false;
	int TARGET_FLAG_8 = false;
	int TARGET_FLAG_9 = false;
	int TARGET_FLAG_10 = false;
		
	int BALL_X = 40;
	int BALL_Y = 10;
	int BALL_X_BIAS = 1;
	int BALL_Y_BIAS = 1;
	int BALL_X_OLD = 40;
	int BALL_Y_OLD = 10;
	
	int BARRA_X = 35;
	int BARRA_X_OLD = 0;
	int BARRA_Y = 20;	
	int BARRA_Y_OLD = 0;	
	
	//Genera que el movimiento siga en el mismo sentido.
	bool BARRA_MOVE = false;
	int AUTO = 0;
	int start_time;
	int RETARDO = 1000/FPS;  	
	bool salir = false;
	int puntaje = 0;
	int angulo = 0;
	
	//Deshabilita el cursor.
	_setcursortype( 0 );
	
	//Dibuja Target	
	int atributo = WHITE << 4 | GREEN;
	textattr( atributo);	
	for(int i=0;i<TARGET_ANCHO;i++)
	{
		gotoxy(TARGET_X+i,TARGET_Y);
		putch(TARGET_FILL);	
	}
	gotoxy(1,1);
	normvideo();
	
	//Dibujar Barra		 
	textbackground( RED );		
	textcolor( LIGHTRED  );	
	for(int i=0;i<BARRA_ANCHO;i++)
	{
		gotoxy(BARRA_X+i,BARRA_Y);
		putch(BARRA_FILL);	
	}
	gotoxy(1,1);
	normvideo();
	
	//Dibujar Bola
	textcolor( WHITE );
	gotoxy(BALL_X,BALL_Y);
	putch(BALL_FILL);
	gotoxy(1,1);
	normvideo();
	
	//Dibuja el puntaje
	gotoxy(1,1);
	printf("Puntaje: %d",puntaje);
	gotoxy(1,1);
	
	//Dibuja el Autoria
	gotoxy(59,25);
	printf("Oscar Sanchez - 2012");
	gotoxy(1,1);
	
	srand(time(NULL));
	
	while(!salir)
	{
		start_time =  clock();
			
		//detectar el teclado
		if(kbhit())
		{
			char key = getch();
			switch(key)
			{
				case KEY_ESC:
				{					
					salir = true;
				}
				break;
				case KEY_LEFT:
				{
					AUTO = AUTO_DEF * -1;					
				}
				break;
				case KEY_RIGHT:
				{					
					AUTO = AUTO_DEF;
				}
				break;				
				default:
				break;
			}			
		}
		
		//Calular movimiento barra y detectar colisiones de limite de venta.	
		if(AUTO < -1)
		{
			if(BARRA_X > LIMIT_LOW_X)
			{
				BARRA_X_OLD = BARRA_X;
				BARRA_X -= 2;
				BARRA_MOVE = true;
			}			
			AUTO++;
		}else if(AUTO > 1)
		{
			if(BARRA_X + BARRA_ANCHO < LIMIT_HIGH_X)
			{
				BARRA_X_OLD = BARRA_X;
				BARRA_X += 2;
				BARRA_MOVE = true;
			}			
			AUTO--;
		}		
		
		//Ajustar limites barra
		if(BARRA_X < LIMIT_LOW_X)
			BARRA_X = LIMIT_LOW_X;
		else if(BARRA_X + BARRA_ANCHO > LIMIT_HIGH_X)
			BARRA_X = LIMIT_HIGH_X - BARRA_ANCHO;
				
		//mover la pelota y detectar colisiones de limite de venta
		BALL_X_OLD = BALL_X;
		BALL_Y_OLD = BALL_Y;
		
		//detectar las colision entre la Pelota y la Barra
		if(BALL_X + BALL_X_BIAS >= BARRA_X &&  BALL_X + BALL_X_BIAS <= BARRA_X + BARRA_ANCHO && BALL_Y + BALL_Y_BIAS == BARRA_Y)
		{
			//Variacion del angulo de rebote y velocidad del rebote
			angulo = rand()%VEL_Y+1;
			if(BALL_Y_BIAS > 0)
				BALL_Y_BIAS = -1 * angulo;
			else
				BALL_Y_BIAS = 1 * angulo;
			
			angulo = rand()%VEL_X+1;
			if(BALL_X_BIAS > 0)
				BALL_X_BIAS = 1 * angulo;
			else
				BALL_X_BIAS = -1 * angulo;			
		}
		
		//Ajuste de colision lateral con la barra
		if(BALL_Y + BALL_Y_BIAS == BARRA_Y)
		{
			BALL_X += BALL_X_BIAS;
			BALL_Y += BALL_Y_BIAS;
		}
		
		//angulo = rand()%VEL_X+1;		
		if(BALL_X >= LIMIT_HIGH_X)
			BALL_X_BIAS *= -1;
		else if(BALL_X <= LIMIT_LOW_X)
			BALL_X_BIAS *= -1;
		
		if(abs(BALL_Y_BIAS)>1)
			angulo = rand()%VEL_Y+1;
		
		if(BALL_Y >= LIMIT_HIGH_Y)
			BALL_Y_BIAS = -1;
		else if(BALL_Y <= LIMIT_LOW_Y)
			BALL_Y_BIAS = 1;
		
		if(abs(BALL_X_BIAS)>1)
			angulo = rand()%VEL_X+1;
		
		if(BALL_X >= LIMIT_HIGH_X)
			BALL_X_BIAS = -1;
		else if(BALL_X <= LIMIT_LOW_X)
			BALL_X_BIAS =  1;
		
		//Colision con el puntaje
		if(BALL_Y + BALL_Y_BIAS == 1)
		{
			if(BALL_X <= 15)
			{
				if(BALL_Y_BIAS > 0)
					BALL_Y_BIAS = -1;
				else
					BALL_Y_BIAS = 1;
			}
		}
		
		BALL_X += BALL_X_BIAS;
		BALL_Y += BALL_Y_BIAS;	
				
		//Correccion de limites
		if(BALL_X > LIMIT_HIGH_X)
			BALL_X = LIMIT_HIGH_X;
		else if(BALL_X < LIMIT_LOW_X)
			BALL_X = LIMIT_LOW_X;
		
		if(BALL_Y > LIMIT_HIGH_Y)
			BALL_Y = LIMIT_HIGH_Y;
		else if(BALL_Y < LIMIT_LOW_Y)
			BALL_Y = LIMIT_LOW_Y;
		
		//Dibujar Pelota
		movetext(BALL_X_OLD, 
				 BALL_Y_OLD,
				 BALL_X_OLD,
				 BALL_Y_OLD,
			     BALL_X,
				 BALL_Y);	
		
		gotoxy(BALL_X_OLD,BALL_Y_OLD);
		putch(CLEAR);
		gotoxy(1,1);
		
		//Dibujar barra. Se redibuja solo cuando esta cambia de lugar.
		if(BARRA_MOVE)
		{
			BARRA_MOVE = false;
			//mover la barra
			movetext(BARRA_X_OLD, 
					 BARRA_Y,
					 BARRA_X_OLD + BARRA_ANCHO,
					 BARRA_Y,
					 BARRA_X,BARRA_Y);
						
			//Deteccion del sentido			
			if(BARRA_X_OLD < BARRA_X)
			{
				for(int i = BARRA_X_OLD;i<BARRA_X;i++)
				{
					gotoxy(i,BARRA_Y);
					putch(CLEAR);
				}
			}
			else
			{
				for(int i = BARRA_X_OLD + BARRA_ANCHO;i>BARRA_X + BARRA_ANCHO;i--)
				{
					gotoxy(i,BARRA_Y);	
					putch(CLEAR);
				}
			}
			gotoxy(1,1);			
		}	
		
		//Calcula puntaje		
		if(BALL_Y == TARGET_Y)
		{
			switch(BALL_X)
			{
				case TARGET_X:
					if(!TARGET_FLAG_1)
					{
						TARGET_FLAG_1 =  true;
						puntaje++;		
					}
				break;
			case TARGET_X+1:
				if(!TARGET_FLAG_2)
				{
					TARGET_FLAG_2 =  true;
					puntaje++;		
				}
				break;
			case TARGET_X+2:
				if(!TARGET_FLAG_3)
				{
					TARGET_FLAG_3 =  true;
					puntaje++;		
				}
				break;
			case TARGET_X+3:
				if(!TARGET_FLAG_4)
				{
					TARGET_FLAG_4 =  true;
					puntaje++;		
				}
				break;			
			case TARGET_X+4:
					if(!TARGET_FLAG_5)
					{
						TARGET_FLAG_5 =  true;
						puntaje++;		
					}
				break;
			case TARGET_X+5:
				if(!TARGET_FLAG_6)
				{
					TARGET_FLAG_6 =  true;
					puntaje++;		
				}
				break;
			case TARGET_X+6:
				if(!TARGET_FLAG_7)
				{
					TARGET_FLAG_7 =  true;
					puntaje++;		
				}
				break;
			case TARGET_X+7:
				if(!TARGET_FLAG_8)
				{
					TARGET_FLAG_8 =  true;
					puntaje++;		
				}
				break;
			case TARGET_X+8:
				if(!TARGET_FLAG_9)
				{
					TARGET_FLAG_9 =  true;
					puntaje++;		
				}
				break;
			case TARGET_X+9:
				if(!TARGET_FLAG_10)
				{
					TARGET_FLAG_10 =  true;
					puntaje++;		
				}
				break;
			}
			if(puntaje == 8)
			{
				salir =  true;
				gotoxy(27,10);
				textbackground( RED );		
				textcolor( WHITE  );
				printf("Felicitaciones has ganado.");
				normvideo();
			}
		}		
		
		//Dibuja el puntaje
		gotoxy(1,1);
		printf("Puntaje: %d",puntaje);
		gotoxy(1,1);
		
		//Genera el retardo de acuerdo al Frames x segundo
		while((clock() - start_time) < RETARDO);			
	}
	gotoxy(27,12);	
	system("Pause");
	_setcursortype( _NORMALCURSOR );
	clrscr();
	gotoxy(27,10);	
	cout<<"Gracias por jugar";	
	gotoxy(27,12);	
	cout<<"Hasta Luego";
	gotoxy(27,14);		
	system("Pause");	
	return 0;
}
