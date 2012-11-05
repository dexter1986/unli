#include<iostream>
#include<constream>
#include<iomanip>
#include<cstdio>
#include<cstdlib>
#include<ctime>

using namespace std;

void dibujarTateti(int arr[][3]);
void turno(bool juegaCruz);
void cambioTurno(bool &turno);
bool validaJugada(int arr[][3],char letra,int nro,bool turno);
bool buscaGanador(int arr[][3]);

int main(int argc,char *argv[])
{
	int tateti[3][3] = { {0,0,0},
						 {0,0,0},
					     {0,0,0}	
					   };	
	char letra;
	int nro;
	bool juegaCruz = true;
	int jugadas = 0;
	bool mostrarError = false;
		
	while(true)
	{	
		dibujarTateti(tateti);
		
		turno(juegaCruz);
		
		if(mostrarError){
			cout<<"El lugar ubicacion no es valida."<<endl<<"Ingrese otra ubicacion."<<endl<<endl;	
			mostrarError = false;
		}
		
		cout<<"Ingrese posicion (ej. a1): ";		
		cin>>letra;				
		cin>>nro;	
		
		if(validaJugada(tateti,letra,nro,juegaCruz))
		{
			if(jugadas>3)
			{
				if(buscaGanador(tateti))
				{
					dibujarTateti(tateti);
					cout<<endl<<endl<<setw(35);
					if(juegaCruz)						
						cout<<"Cruz(X)";
					else
						cout<<"Circulo(O)";
					cout<<" GANA...!!"<<endl<<endl;
					break;
				}else{
					if(jugadas==8)
					{
						dibujarTateti(tateti);
						cout<<endl<<endl<<setw(35);
						cout<<"Juego empatado"<<endl<<endl;
						break;
					}
				}				
			}			
			cambioTurno(juegaCruz);
			jugadas++;
			
		}else
		{
			mostrarError = true;
		}
		//Borra el buffer del teclado
		cin.clear();
		cin.sync();
	}
	cout<<"Gracias por jugar."<<endl<<endl;
	system("PAUSE");
	return 0;
}

bool buscaGanador(int arr[][3])
{
	
	if(arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2] && arr[2][2]>0)
	{
		return true;
	}else if(arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0] && arr[2][0]>0)
	{
		return true;
	}
	
	for(int x=0;x<3;x++)
	{		
		if(arr[x][0] == arr[x][1] &&  arr[x][1] == arr[x][2] && arr[x][2] > 0)
			return true;
	}
	
	for(int x=0;x<3;x++)
	{		
		if(arr[0][x] == arr[1][x] &&  arr[1][x] == arr[2][x] && arr[2][x] > 0)
			return true;
	}
	
	return false;
}

bool validaJugada(int arr[][3],char letra,int nro,bool turno)
{
	int x,y;
	y = nro-1;
	switch(letra)
	{
		case 'A':
		case 'a':
			x = 0;
			break;
		case 'B':
		case 'b':
			x = 1;
			break;
		case 'C':
		case 'c':
			x = 2;
			break;
		default:
			return false;			
	}
	
	if(x>-1 && x<3&& y>-1 && y<3)
	{
		if(arr[x][y] == 0)
		{
			if(turno)						
				arr[x][y] = 1;
			else
				arr[x][y] = 2;
				
			return true;
		}
	}
	return false;	
}

void turno(bool turno)
{
	if(turno)
		cout<<"Es el turno de Cruz (X)"<<endl;
	else
		cout<<"Es el turno de Circulo (O)"<<endl;
	
	cout<<endl;
}

void cambioTurno(bool &turno)
{
	turno = !turno;
}

void dibujarTateti(int arr[][3])
{
	clrscr();
	cout<<endl<<setw(40)<<"TATETI"<<endl<<endl<<endl;	
	for(int i=0;i<3;i++)
	{
		cout<<setw(33);
		cout<<(char)(65+i)<<"  ";
		for(int x=0;x<3;x++)
		{			
			switch(arr[i][x])
			{
				case 0:
					cout<<" ";
					break;
				case 1:
					cout<<"X";
					break;
				case 2:
					cout<<"O";
					break;
			}
			if(x<2)
				cout<<(char)179;
		}
		cout<<endl;
		if(i<2)
			cout<<setw(35)<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<(char)196<<endl;
	}
	cout<<setw(35)<<"1"<<"  "<<"2"<<"  "<<"3"<<endl;
}



