#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstdio>
#include<cstdlib>
#include<ctime>

using namespace std;
#define PI 3.14162
#define G 9.8 

int main(int argc,char *argv[])
{
	float grad;
	float rad;
	cout<<"Ingrese un angulo en grados"<<endl;
	cin>>grad;
	rad = grad*PI/180;
	cout<<rad<<" radianes"<<endl;
	cout<<"Ingrese un angulo en radianes"<<endl;
	cin>>rad;
	grad = rad*180/PI;
	cout<<grad<<" grados"<<endl;	
	
	cout<<"Ingrese el valor de la altura"<<endl;
	float altura;
	cin>>altura;
	float tiempo;
	tiempo = sqrt(2*altura/G);	
	cout<<tiempo<<" segundos"<<endl;	
	system("PAUSE");
	return 0;
}
