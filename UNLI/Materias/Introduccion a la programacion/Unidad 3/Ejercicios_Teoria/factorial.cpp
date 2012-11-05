#include<iostream>
#include<cmath>
#include<cstdio>
#include<ctime>
#include<cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
	int nro;
	unsigned int fact = 1;
    cout << "Factorial de un nro\n";
	cout << "Ingrese un nro: ";
	cin >> nro;
	
	if(nro<=0)
	{
		cout << "El nro debe ser mayo a cero (0)"<<endl;
	}
	else{
		cout << "Calulando Factorial..\n";
		for(int i=0;i<nro;i++)
		{
			fact *= i + 1;
		}
		cout << "El factorial de "<<nro<<" es "<< fact<<endl;
	}
	system("PAUSE");
	return 0;
}
