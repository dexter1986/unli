#include<constream>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<iomanip>
#include<ctime>

using namespace conio;
using namespace std;

void intercambio(int &v1,int &v2);
void intercambio(char &v1,char &v2);
void intercambio(float &v1,float &v2);
	
int main(int argc,char *argv[])
{
	int v1=4,v2=5;
	cout<<"Valor1: "<<v1<<" Valor2: "<<v2<<endl;
	cout<<"Intercambio"<<endl;
	intercambio(v1,v2);
	cout<<"Valor1: "<<v1<<" Valor2: "<<v2<<endl;
	cout<<"------------------------------------"<<endl;
	float vf1=4.1,vf2=5.3;
	cout<<"Valor1: "<<vf1<<" Valor2: "<<vf2<<endl;
	cout<<"Intercambio"<<endl;
	intercambio(vf1,vf2);
	cout<<"Valor1: "<<vf1<<" Valor2: "<<vf2<<endl;
	cout<<"------------------------------------"<<endl;
	char vc1='A',vc2='Z';
	cout<<"Valor1: "<<vc1<<" Valor2: "<<vc2<<endl;
	cout<<"Intercambio"<<endl;
	intercambio(vc1,vc2);
	cout<<"Valor1: "<<vc1<<" Valor2: "<<vc2<<endl;
	cout<<"------------------------------------"<<endl;	
	system("PAUSE");
	return 0;
}

void intercambio(int &v1,int &v2)
{
	int aux = v1;
	v1 = v2;
	v2 = aux;
}

void intercambio(char &v1,char &v2)
{
	char aux = v1;	
	v1 = v2;
	v2 = aux;
}

void intercambio(float &v1,float &v2)
{
	float aux = v1;	
	v1 = v2;
	v2 = aux;
}
