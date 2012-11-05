#include<iostream>
#include<cmath>
#include<cstdio>
#include<ctime>
#include<cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
	int d1;
	int d2;	
	int d1_temp,d2_temp;		
    int tiradas;
    cout << "Lanzamiento de 2 dados de 10 caras."<<endl<<"Se mostraran todos los resultados."<<endl<<"Se elegira el mejor de ellos.\n";	
	cout <<endl<< "Ingrese la cantidad de tiradas: ";
	cin >> tiradas;
	
	srand(time(NULL));
		
	for(int i=0;i<tiradas;i++)
	{
		d1_temp = rand()%10+1;		
		d2_temp = rand()%10+1;
		
		if(i==0)
		{
		   d1 = d1_temp;
		   d2 = d2_temp;
		}
		else{
		    if(d1+d2 < d1_temp+d2_temp)
			{
				d1 = d1_temp;
				d2 = d2_temp;
			}
		}			
		cout <<d1_temp<<" "<<d2_temp<<" total: "<<d1_temp+d2_temp<<endl;
	}
	
	cout << "La mejor tirada fue "<<d1<<" "<<d2<<" total "<<d1+d2<<endl;
		
	system("PAUSE");
	return 0;
}
