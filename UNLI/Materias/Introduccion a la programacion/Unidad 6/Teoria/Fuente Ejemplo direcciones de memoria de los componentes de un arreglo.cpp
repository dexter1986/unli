#include <iostream>


using namespace std;
int main(int argc, char *argv[]) {
	int x[]={12,13,14,15,16};
	for (int i=0; i<5; i++)
		cout<<&x[i]<<endl;
	return 0;
}
