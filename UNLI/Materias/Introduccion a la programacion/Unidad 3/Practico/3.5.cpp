#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<ctime>

using namespace std;

int main(int argc,char *argv[])
{
	int d1,d2; //Dados
	srand(time(NULL));
	
	d1 = rand()%6+1; //con 6 caras
	d2 = rand()%6+1;
	cout<<"Se lanzan 2 dados de 6 caras."<<endl<<"Este es el resultado:"<<endl;
	cout<<"Tirada: "<<d1<<" "<<d2<<endl;
	cout<<"Los dados ";
	if(d1==d2)
		cout<<"son";
	else
		cout<<"no son";
	cout<<" iguales."<<endl;
	cout<<"La suma de ambos es: "<<d1+d2<<endl;
	system("PAUSE");
	return 0;
}
