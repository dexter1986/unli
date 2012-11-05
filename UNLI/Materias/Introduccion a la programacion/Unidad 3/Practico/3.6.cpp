#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<ctime>

using namespace std;

int main(int argc,char *argv[])
{
	int d1,d2; //Dados
	int arma,escudo;
	int danio;
		
	srand(time(NULL));
	//Calculo del arma 2d6+3
	d1 = rand()%6+1;
	d2 = rand()%6+1;
	arma = d1 + d2 + 3;
	
	cout<<endl<<"Personaje A golpea con un arma "<<d1<<" "<<d2<< " +3"<<endl;
	
	//calculo del escudo 2d4+1
	d1 = rand()%4+1;
	d2 = rand()%4+1;
	escudo = d1+d2+1;
	
	cout<<"Personaje B usa el escudo con  "<<d1<<" "<<d2<< " +1"<<endl;
	
	danio = arma - escudo;
	
	cout<<endl<<"Personaje B ";
	
	if(danio <= 0)	
		cout<<"no recibe danio."<<endl;
	else
		cout<<"recibe +"<<danio<<" puntos danio."<<endl<<endl;
	
	system("PAUSE");
	return 0;
}
