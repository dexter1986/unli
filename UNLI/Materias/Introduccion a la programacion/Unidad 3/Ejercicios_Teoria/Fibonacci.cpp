#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>

using namespace std;

int main(int argc,char *argv[])
{
	int nro;
	unsigned int A=0;
	unsigned int B=1;
	unsigned int C=1;
	char sep = ',';
	cout<<"Serie Fibonacci\n";
	cout<<"Ingrese un numero: ";
	cin>> nro;
	cout<<"Calculando serie Fibonacci\n";	
	cout << "La serie Fibonacci de "<<nro<<": ";
	
	if(nro>=0)
	{
		cout<<A;		
	}
	if(nro>=1)
	{
		cout<<sep<<B;		
	}
	
	for(int i=1;i<nro;i++)
	{
		C = A + B;		
	    cout<<sep<<C;
		A = B;
		B = C;
	}
	cout<<endl;
	system("PAUSE");
	return 0;
}
