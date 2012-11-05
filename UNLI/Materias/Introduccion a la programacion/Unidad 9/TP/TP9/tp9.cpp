#include<iostream>
#include<ctime>
#include<cstdio>
#include<stdlib.h>
#include<iomanip>
#include<conio2.h>
#include<windows.h>

using namespace std;

class Animal
{
protected:
	int color;
	
public:
	Animal();
	virtual void dibujar()=0;
	virtual void comer()=0;
	virtual void hacerRuido()=0;
};

Animal::Animal()
{
	color = rand()%10+1;
}

class Vaca: public Animal
{
private:
	int M[4][3];
public:
	Vaca();
	void dibujar();
	void comer();
	void hacerRuido(); 
};

class Pato : public Animal {
private:
	int M[5][3];
public:
	Pato();
	void dibujar();
	void comer();
	void hacerRuido();
};

class Chancho : public Animal {
private:
	int M[6][2];
public:
	Chancho();
	void dibujar();
	void comer();
	void hacerRuido(); 
};

void Vaca::dibujar()
{	
	textcolor(color);
	int x = wherex();
	int y = wherey();
	
	for(int i=0;i<3;i++)
	{
		gotoxy(x,y+i);
		for(int z=0;z<4;z++)
		{
			putch(M[z][i]);
		}
	}
	normvideo();
}

void Vaca::comer()
{
	cout<<"NIAM NIAM!";
}

void Vaca::hacerRuido()
{
	cout<<"MUUUUU!";
}

Vaca::Vaca()
{
	M[0][0] = 40; M[0][1] = 40; M[0][2] = 0;
	M[1][0] = 95; M[1][1] = 186; M[1][2] = 92;
	M[2][0] = 95; M[2][1] = 186; M[2][2] = 47;
	M[3][0] = 41; M[3][1] = 41; M[3][2] = 0;
}

Pato::Pato() {
	M[0][0] = 0; M[0][1] = 62; M[0][2] = 0;
	M[1][0] = 0; M[1][1] = 40; M[1][2] = 0;
	M[2][0] = 95;M[2][1] = 39; M[2][2] = 41;
	M[3][0] = 95;M[3][1] = 0;  M[3][2] = 47;
	M[4][0] = 0; M[4][1] = 41; M[4][2] = 0;
}

void Pato::dibujar()
{
	textcolor(color);
	int x = wherex();
	int y = wherey();
	
	for(int i=0;i<3;i++)
	{
		gotoxy(x,y+i);
		for(int z=0;z<5;z++)
		{
			putch(M[z][i]);
		}
	}
	normvideo();
}

void Pato::comer()
{
	cout<<"NIAM NIAM!";
}

void Pato::hacerRuido()
{
	cout<<"CUAC CUAC!";
}

Chancho::Chancho() {	
	M[0][0] = 94; M[0][1] = 0;
	M[1][0] = 46; M[1][1] = 40;
	M[2][0] = 0; M[2][1] = 186;
	M[3][0] = 0; M[3][1] = 186;
	M[4][0] = 46; M[4][1] = 41;
	M[5][0] = 94; M[5][1] = 0;
}

void Chancho::dibujar()
{
	textcolor(color);
	int x = wherex();
	int y = wherey();
	
	for(int i=0;i<2;i++)
	{
		gotoxy(x,y+i);
		for(int z=0;z<6;z++)
		{
			putch(M[z][i]);
		}
	}
	normvideo();
}

void Chancho::comer()
{
	cout<<"RGRAM RGRAM!";
}

void Chancho::hacerRuido()
{
	cout<<"OINK OINK!";
}

int main(int argc,char *argv[])
{
	srand(time(NULL));
	Animal *animales[3];
	Animal *animales_tmp[3];
	animales[0] = new Vaca();
	animales[1] = new Chancho();
	animales[2] = new Pato();
	
	animales_tmp[0] = animales[0];
	animales_tmp[1] = animales[1];
	animales_tmp[2] = animales[2];
	
	bool salir = false;
	bool comen = false;
	bool ruido = false;
	while(!salir)
	{	
		gotoxy(5,10+5);
		cout<<"                                           ";
		for(int i=0;i<3;i++)
		{
			gotoxy(7+(i*15),10);
			animales[i]->dibujar();		
			gotoxy(5+(i*15),10+5);
			if(comen)
			{	
				animales[i]->comer();
			}else if(ruido)
			{	
				animales[i]->hacerRuido();
			}
		}
		
		comen = false;
		ruido = false;
		
		char op = getch();
		
		switch(op)
		{
			case '1':
				clrscr();
				animales[0] = animales_tmp[0];
				animales[1] = animales_tmp[1];
				animales[2] = animales_tmp[2];				
				break;
			case '2':
				clrscr();
				animales[0] = animales_tmp[2];
				animales[1] = animales_tmp[0];
				animales[2] = animales_tmp[1];
				break;
			case '3':
				clrscr();
				animales[0] = animales_tmp[1];
				animales[1] = animales_tmp[2];
				animales[2] = animales_tmp[0];
				break;
			case '4':	
				comen = true;
				break;
			case '5':	
				ruido = true;
				break;
			case 27:
				salir = true;
				break;
		}
	}
	
	for(int i=0;i<3;i++)
	{
		delete animales[i];
	}
	
	return 0;
}
