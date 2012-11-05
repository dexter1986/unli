#include<iostream>
#include<ctime>
#include<cstdio>
#include<stdlib.h>
#include<iomanip>
#include<conio.h>
#include<conio2.h>
#include<windows.h>

using namespace std;

class Pez
{
private:
	int top_contador;
	int contador;
	void contar();
	int con_vel;
protected:
	int old_pos_x;
	int pos_x;
	int lim_x;	
	int old_pos_y;
	int pos_y;
	int lim_y;
	int color;
	int direccion;
	int velocidad;
	int top_x;
	int top_y;
	virtual int get_graf_der(int x,int y)=0;
	virtual int get_graf_izq(int x,int y)=0;
	virtual void det_velocidad()=0;
	void cambiarColor();
	void cambiarDireccion();
public: 
	Pez();
	void mover();
	void dibujar();
};

void Pez::dibujar()
{
	int grafico;
	
	textcolor(0);
	
	if(old_pos_y > pos_y)
	{
		gotoxy(old_pos_x,old_pos_y+lim_y-1);		
		cout<<"          ";
	}
	else if(old_pos_y < pos_y)
	{
		gotoxy(old_pos_x,old_pos_y);
		cout<<"          ";
	}
	
	for(int y=0;y<top_y;y++)
	{
		if(direccion == 0)			
			putchxy(old_pos_x,old_pos_y+y,' ');
		else
			putchxy(old_pos_x+lim_x-1,old_pos_y+y,' ');
	}
	
	textcolor(color);
	for(int y=0;y<top_y;y++)
	{
		for(int x=0;x<top_x;x++)
		{
			if(direccion == 0)
				grafico = get_graf_der(x,y);
			else
				grafico = get_graf_izq(x,y);
			
			putchxy(pos_x+x,pos_y+y,grafico);
		}
	}
}

Pez::Pez()
{
	top_contador = rand()%10+30;
	pos_y = rand()%14+10;
	pos_x = rand()%20+30;
	color = rand()%7+1;
	direccion = rand()%2;	
	con_vel = 0;
}


void Pez::contar()
{
	contador++;
	if(contador>top_contador)
		contador = 0;
}

void Pez::cambiarColor()
{
	color = rand()%7+1;
}

void Pez::cambiarDireccion()
{
	if(direccion == 0)
		direccion = 1;
	else
		direccion = 0;
}

void Pez::mover()
{
	con_vel--;
	if(con_vel <= 0)
	{
		con_vel = velocidad;
		if(rand()%2==0)
			det_velocidad();
	}
	else
		return;
	
	contar();
	
	if(contador == rand()%30)
	{
		cambiarDireccion();
	}
	
	old_pos_x = pos_x;	
	old_pos_y = pos_y;
		
	if(rand()%3==0)
	{
		if(rand()%3==0)
			pos_y--;
		else
			pos_y++;
	}	
	
	if(direccion == 0)
		pos_x++;
	else
		pos_x--;
	
	if(pos_x > 80 - lim_x)
	{
		pos_x = 80 - lim_x;
		cambiarDireccion();
	}else if(pos_x<1)
	{
		pos_x = 1;
		cambiarDireccion();
	}
	
	if(pos_y > 25-lim_y)
	{
		pos_y = 25-lim_y;		
	}else if(pos_y < 1)
	{
		pos_y = 1;		
	}
}

class Pez_1: public Pez
{	
private:
	//Direccion Derecha
	int f0[10][4];	
	//Direccion Izquierda
	int f1[10][4];	
	
protected:
	void det_velocidad();	
	int get_graf_izq(int x,int y);
	int get_graf_der(int x,int y);
public:
	void cambiarColor();
	Pez_1();	
};
Pez_1::Pez_1()
{
	lim_x = 10;
	lim_y = 4;
	top_x = 10;
	top_y = 4;
	det_velocidad();
	//Direccion Derecha	
	f0[0][0]=0;f0[0][1]=0;f0[0][2]=41;f0[0][3]=41;
	f0[1][0]=0;f0[1][1]=0;f0[1][2]=92;f0[1][3]=47;
	f0[2][0]=0;f0[2][1]=0;f0[2][2]=47;f0[2][3]=39;
	f0[3][0]=0;f0[3][1]=46;f0[3][2]=0;f0[3][3]=39;
	f0[4][0]=0;f0[4][1]=45;f0[4][2]=0;f0[4][3]=39;
	f0[5][0]=124;f0[5][1]=0;f0[5][2]=40;f0[5][3]=39;
	f0[6][0]=92;f0[6][1]=0;f0[6][2]=40;f0[6][3]=39;
	f0[7][0]=0;f0[7][1]=45;f0[7][2]=0;f0[7][3]=45;
	f0[8][0]=0;f0[8][1]=46;f0[8][2]=111;f0[8][3]=45;
	f0[9][0]=0;f0[9][1]=0;f0[9][2]=92;f0[9][3]=39;
	
	//Direccion Izquierda
	f1[0][0]=0;f1[0][1]=0;f1[0][2]=47;f1[0][3]=39;
	f1[1][0]=0;f1[1][1]=46;f1[1][2]=111;f1[1][3]=45;
	f1[2][0]=0;f1[2][1]=45;f1[2][2]=0;f1[2][3]=45;
	f1[3][0]=47;f1[3][1]=0;f1[3][2]=41;f1[3][3]=39;
	f1[4][0]=124;f1[4][1]=0;f1[4][2]=41;f1[4][3]=39;
	f1[5][0]=0;f1[5][1]=45;f1[5][2]=0;f1[5][3]=39;
	f1[6][0]=0;f1[6][1]=46;f1[6][2]=0;f1[6][3]=39;
	f1[7][0]=0;f1[7][1]=0;f1[7][2]=92;f1[7][3]=39;
	f1[8][0]=0;f1[8][1]=0;f1[8][2]=47;f1[8][3]=92;
	f1[9][0]=0;f1[9][1]=0;f1[9][2]=40;f1[9][3]=40;
	
}

void Pez_1::cambiarColor()
{
	Pez::cambiarColor();
}

void Pez_1::det_velocidad()
{
	velocidad = rand()%2+1;
}


int Pez_1::get_graf_der(int x,int y)
{
	return f0[x][y];
}

int Pez_1::get_graf_izq(int x,int y)
{
	return f1[x][y];
}

class Pez_2 : public Pez
{
private:
	//Direccion Derecha
	int f0[6][2];
	//Direccion Izquierda	
	int f1[6][2];	
	
protected:
	void det_velocidad();
	int get_graf_izq(int x,int y);
	int get_graf_der(int x,int y);
public:
	Pez_2();	
	void cambiarDireccion();
};

void Pez_2::cambiarDireccion()
{
	Pez::cambiarDireccion();
}

Pez_2::Pez_2()
{
	lim_x = 6;
	lim_y = 2;
	det_velocidad();
	top_x = 6;
	top_y = 2;
	//Direccion Derecha
	f0[0][0]=92;	
	f0[0][1]=47;
	f0[1][0]=95;f0[1][1]=45;
	f0[2][0]=124;f0[2][1]=46;
	f0[3][0]=92;f0[3][1]=40;
	f0[4][0]=0;f0[4][1]=39;
	f0[5][0]=0;f0[5][1]=62;
	
	//Direccion Izquierda		
	f1[0][0]=0;f1[0][1]=60;
	f1[1][0]=0;f1[1][1]=39;
	f1[2][0]=47;f1[2][1]=41;
	f1[3][0]=124;f1[3][1]=46;
	f1[4][0]=95;f1[4][1]=45;
	f1[5][0]=47;f1[5][1]=92;	
	
	
}
void Pez_2::det_velocidad()
{
	velocidad = rand()%2;
}

int Pez_2::get_graf_der(int x,int y)
{
	return f0[x][y];
}

int Pez_2::get_graf_izq(int x,int y)
{
	return f1[x][y];
}

class Juego
{
private:
	Pez_1 pez1a;
	Pez_1 pez1b;
	
	Pez_2 pez2a;
	Pez_2 pez2b;
	
	void obtenerTeclas();
	void dibujar();
	void mover();
	
public:
	void loop();	
};

void Juego::obtenerTeclas()
{
	if(kbhit())
	{
		int tecla = getch();
		if(tecla == '2')
		{
			pez1a.cambiarColor();
			pez1b.cambiarColor();
		}else if(tecla == '1')
		{
			pez2a.cambiarDireccion();
			pez2b.cambiarDireccion();
		}
	}
}

void Juego::mover()
{
	pez1a.mover();
	pez1b.mover();
	pez2a.mover();
	pez2b.mover();
}

void Juego::dibujar()
{	
	pez1a.dibujar();
	pez1b.dibujar();
	pez2a.dibujar();
	pez2b.dibujar();
	gotoxy(59,25);
	normvideo();
	cout<<"Oscar Sanchez - 2012";
}
void Juego::loop()
{
	while(true)
	{
		obtenerTeclas();		
		mover();
		dibujar();
		Sleep(30);
	}
}

int main(int argc,char *argv[])
{
	srand(time(NULL));
	Juego juego;
	juego.loop();
	system("pause");
	return 0;
}

