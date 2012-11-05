#include<cstdio>
#include<iostream>
#include<string.h>
#include<conio2.h>
#include<cstdlib>
#include<ctype.h>
#include<fstream>

using namespace std;

int main(int argc,char *argv[])
{
	char data[255];
	cout<<"Ingrese un texto: ";
	gets(data);
	fstream file;
	file.open("6.7.txt",ios::out|ios::app);	
	file<<data<<endl;
	file.close();
	return 0;
}
