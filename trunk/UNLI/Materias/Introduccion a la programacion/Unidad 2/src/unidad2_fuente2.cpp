#include <iostream>
using namespace std;  
int main(void)
{
	int a=54; 
	{ // inicio del bloque anidado
		int b = 20;
		char a = 'Z' ;
		cout << a <<" "<<b<<"\n";
	} // fin del bloque anidado
	cout <<a<<" "<<b<<"\n" ; 
	return 0;
}


