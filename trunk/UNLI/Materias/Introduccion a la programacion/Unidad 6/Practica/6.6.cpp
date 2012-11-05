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
	fstream file;
	file.open("nota.txt",ios::in);
	file.getline(data,255);
	file.close();
	cout<<data;
	return 0;
}
