#include <iostream>
using namespace std;
void intercambio(int *p,int *q);
int main(int argc, char *argv[]) {
	int x,y;
	cout<<"Primer dato:\n x=" ; cin>>x;
	cout<<"Segundo dato:\n y=" ; cin>>y;
	cout<<&x<<" "<<&y<<endl;
	intercambio(&x,&y);
	cout<<"\n\nDespues de llamar a la funcion intercambio(x,y)";
	cout<<"\n x="<<x<<" y="<<y<<endl;
	cout<<&x<<" "<<&y<<endl;
	
	return 0;
}
void intercambio(int *p,int *q)
{ 
	int aux=*p; *p= *q; *q=aux;
}


