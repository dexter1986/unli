#include<cstdio>
#include<iostream>
#include<string.h>
#include<conio.h>
#include<conio2.h>
#include<cstdlib>
#include<ctype.h>
#include<fstream>
#include<ctime>
#include<windows.h>

using namespace std;

class Pelota
{
private:
	char grafico;
	int color;
	int old_pos_x;
	int old_pos_y;
	int pos_x;
	int pos_y;
	int off_x;
	int off_y;
	int vel;
	void mover();
	void borrar();
public:
	Pelota(int color);
	void dibujar();
};

Pelota::Pelota(int col)
{	
	
	grafico = 'O';
	
	color = col;
	
	pos_x = rand()%80+1;
	pos_y = rand()%25+1;
	
	old_pos_x = pos_x;
	old_pos_y = pos_y;
	
	off_x = rand()%1 == 0 ? 1 : -1;
	off_y = rand()%1 == 0 ? 1 : -1;
	vel = rand()%3+1;
}

void Pelota::mover()
{	
	bool isCol = false;
	
	old_pos_x = pos_x;
	old_pos_y = pos_y;
	
	pos_x += off_x * vel;
	pos_y += off_y * vel;
	
	if(pos_y<1)
	{
		pos_y = 1;
		off_y *= -1;		
		isCol = true;
	}else if(pos_y>25)
	{
		pos_y = 25;
		off_y *=-1;
		
		isCol = true;
	}
	
	if(pos_x<1)
	{
		pos_x = 1;
		off_x *= -1;		
		isCol = true;
	}else if(pos_x>80)
	{
		pos_x = 80;
		off_x *=-1;		
		isCol = true;
	}
	
	if(isCol)
	{
		vel = rand()%3+1;
	}
}

void Pelota::dibujar()
{
	borrar();		
	textcolor(color);		
	putchxy(pos_x,pos_y,grafico);
	mover();	
}

void Pelota::borrar()
{
	textcolor(0);
	putchxy(old_pos_x,old_pos_y,' ');	
}

int main(int argc,char *argv[])
{
	srand(time(NULL));
	int cant = rand()%30+10;
	
	Pelota **pelotas;
	pelotas = new Pelota*[cant];
	
	for(int i=0;i<cant;i++)
	{
		pelotas[i] = new Pelota(rand()%15+1);		
	}
	
	while(true)
	{
		if(kbhit())
		{
			int tecla=getch();
			if(tecla == 27)
				break;
		}
		for(int i=0;i<cant;i++)
		{
			pelotas[i]->dibujar();		
		}
		
		Sleep(50);
	}
	
	for(int i=0;i<cant;i++)
	{
		delete pelotas[i];
	}
	
	system("PAUSE");
	return 0;
}
