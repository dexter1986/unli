#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<ctime>

using namespace std;
//Nota:
//El enunciado del ejercicio no estaba muy claro, lo que entendi fue lo siguiente:
//Si me acerco es caliente, si me alejo es frio, si sigo igual es templado
//Si la diferencia entre el anterior y el numero secreto es mayor a la del numero
//elegido y el numero secreto es caliente, es decir me acerco.
//Si la diferencia entre el anterior y el numero secreto es menor a la del numero
//elegido y el numero secrete es frio, es decir me alejo.
int main(int argc,char *argv[])
{
	int secreto;
	int numero;
	int na;
	int da,ds; 
	bool esPrimerIntento = true;
		
	cout<<"Debes adivinar el numero secreto."<<endl<<endl;	
	
	srand(time(NULL));
	secreto = rand()%20+1; //entre 1 y 20
	
	do
	{	
		cout<<endl<<"Elige un numero: ";
		cin>>numero;
		
		if(esPrimerIntento)
		{
			esPrimerIntento = false;
			if(secreto != numero)				
				cout<<"No hacertaste, intentalo otra vez."<<endl;
		}		
		else if(numero != secreto){	
			da = abs(na - secreto);
			ds = abs(numero - secreto);
			if(da>ds)
				cout<<"Caliente."<<endl;
			else if(da == ds)
				cout<<"Templado."<<endl;
			else
				cout<<"Frio."<<endl;				
		}
		na = numero;
	}while(secreto != numero);
	
	cout<<endl<<"Muy bien..!! hacertaste el numero."<<endl<<endl;
		
	cout<<endl<<"Hasta luego."<<endl<<endl;
	system("PAUSE");
	return 0;
}
