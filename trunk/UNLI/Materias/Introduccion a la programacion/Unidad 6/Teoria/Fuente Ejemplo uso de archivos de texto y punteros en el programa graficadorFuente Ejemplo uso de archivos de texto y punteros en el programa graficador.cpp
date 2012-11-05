#include <iostream>
#include <conio2.h>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;

void imprdib(char map[][10],int alto,int ancho);
void imprmen(char men[][28],int cx,int cy);
void quitacursor(char men[][28],int cx,int cy);
void ponecursor(char men[][28],int cx,int cy);
void mensimple(void);
void mendoble(void);
void dibsimple(int ancho,int alto);
void dibdoble(int ancho,int alto);
void imprayuda(void);

int main(int argc, char *argv[]) {
	
	char map[10][10]; //mapa del gr?fico
	char men[8][28]; //men? de carateres
	char *p; // puntero a char para llenar el menu m?s facilmente
	
	char t; //para leer el teclado
	
	char nombre[256]; //nombre de archivo
	char cad[11]; //cadena auxiliar para ayudar a guardar o leer de los archivos
	ofstream sal; //manejador de archivo de salida
	//ifstream ent; //manejador de archivo de entrada
	
	bool salir=true; //salir=false para salir
	
	int cx,cy; //coordenadas del juego de carateres
	int px,py; //coordenadas del pincel
	
	int alto=3; //alto del mapa gr?fico
	int ancho=3; //ancho del mapa gr?fico
	
	int modo=0; //modo=0 edici?n   modo=1 busqueda caracter
	
	int m,n; //auxiliares para for

	//armamos el men? de caracteres
	
	//este men? es una matriz de 8x28
	//se necesitan colocar todos los caracteres desde el 32 hasta el 255
	//haciendo un doble for se necesitar?an dos variables para cada bucle
	//y un contador de 32 a 256
	//usando punteros solo se necesita un for de 32 a 256
	//esto es as? porque las lineas de una matriz se almacenan una a continuaci?n
	//de otra en la memoria
	
	p=&men[0][0]; //p apunta a men[0][0]
	for(int n=32;n<256;++n)
	{
		*p=char(n); //colocamos el char n en donde apunta p
		++p; // avanzamos p
	}
	
	//iniciamos el mapa del gr?fico con espacios
	for(n=0;n<10;++n)
		for(int m=0;m<10;++m) map[n][m]=' ';
	
	cx=cy=0; // coordenadas caracter en la matriz men? de caracteres
	px=py=0; // coordenadas del pincel para dibujar
	imprdib(map,alto,ancho); //imprimimos la zona de dibujo
	imprmen(men,cx,cy); //imprimimos el men?
	
	imprayuda();
		
	gotoxy(py+2,px+2); //fijamos el cursor en su lugar
	
	while(salir)
	{
		if(kbhit())
		{
			t=getch();
			if(t==27) //tecla Esc salimos del programa
			{
				exit(0);
			}
			if(t==75) //nos movemos a la izquierda
			{
				if(modo==0) //movemos el cursor en el dibujo
				{
					if(py>0) --py;
				}
				
				if(modo==1)
				{
					if(cy>0) //movemos el cursor en el men?
					{
						quitacursor(men,cx,cy);
						--cy;
						ponecursor(men,cx,cy);
					}
				}
				if(modo==2) //mocemos los l?mites del dibujo
				{
					if(ancho>1)
					{
						--ancho;
						imprdib(map,alto,ancho);
						if(py>ancho-1) py=ancho-1;//ajustamos la posici?n del cursor
					}
				}
			}
			if(t==77) //nos movemos a la derecha
			{
				if(modo==0)
				{
					if(py<ancho-1) ++py;
				}
				
				if(modo==1)
				{
					if(cy<27)
					{
						quitacursor(men,cx,cy);
						++cy;
						ponecursor(men,cx,cy);
					}
				}
				if(modo==2)
				{
					if(ancho<10)
					{
						++ancho;
						imprdib(map,alto,ancho);
					}
				}
			}
			if(t==72) //nos movemos hacia arriba
			{
				if(modo==0)
				{
					if(px>0) --px;
				}
				
				if(modo==1)
				{
					if(cx>0) 
					{
						quitacursor(men,cx,cy);
						--cx;
						ponecursor(men,cx,cy);
					}
				}
				if(modo==2)
				{
					if(alto>1)
					{
						--alto;
						imprdib(map,alto,ancho);
						if(px>alto-1) px=alto-1; //ajustamos la posici?n del cursor
					}
				}
			}
			if(t==80) //nos movemos hacia abajo
			{
				if(modo==0)
				{
					if(px<alto-1) ++px;
				}
				
				if(modo==1)
				{
					if(cx<7)
					{
						quitacursor(men,cx,cy);
						++cx;
						ponecursor(men,cx,cy);
					}
				}
				if(modo==2)
				{
					if(alto<10)
					{
						++alto;
						imprdib(map,alto,ancho);
					}
				}
			}
			
			if(t==9) //Tecla Tabulador cambia de modo
			{
				if(modo==0)
				{
					//sacamos el resaltado al dibujo
					dibsimple(alto,ancho);
					
					//reborde resaltado en el men?
					mendoble();
					
					modo=1; //cambiamos el modo
				}
				else
					if(modo==1)
					{
						//colocamos el resaltado al dibujo
						dibdoble(alto,ancho);
						
						//sacamos resaltado en el men?
						mensimple();
						
						modo=0; //cambiamos el modo
					}
			}
			
			if((t==32)&&((modo==0)||(modo==1))) //pintamos con espacio solo en modo 0 o 1
			{
				map[px][py]=men[cx][cy]; //b?sicamente se pasa el caracter que est?
				putchar(map[px][py]); //se?alado en el men? a la posici?n que est?
				                      //se?alada en el dibujo
			}
			
			if((t==13)&&(modo==0)) //cambiamos el tama?o del dibujo solo em modo 0
			{
				modo=2; //no se dibuja, se cambia el tama?o
				
				//resaltamos dibujo para hacer notar que se esta cambiando su tama?o
				highvideo();
				imprdib(map,alto,ancho); //imprimimos el nuevo tama?o
			}
			else
				if((t==13)&&(modo==2)) //terminamos de cambiar el tama?o
				{
					modo=0; //volvemos al modo edici?n
					//normalizamos el cuadro de dibujo para se?alar que ahora se edita
					normvideo();
					imprdib(map,alto,ancho); //imprimimos el dibujo pero sin resaltado
				}
			
			if((t==60)&&(modo==0))//F2 para guardar solo en modo 0
			{
				gotoxy(1,23);
				cout<<"Introduce el nombre del archivo a guardar:";
				cin.getline(nombre,256);
				sal.open(nombre); //abrimos el archivo para escritura nombre
				
				for(int n=0;n<alto;++n) //leemos linea por linea el dibujo
				{
					strncpy(cad,map[n],ancho); //copiamos la linea a una cadena
					cad[ancho]=0; //por un bug en el compilador hay que agregar '\0'
					sal<<cad<<endl; //enviamos la linea al archivo con un enter al final
				}
				sal.close(); //cerramos el archivo y se puede reutilizar sal la pr?xima vez
				gotoxy(1,23); //borramos el pedido de nombre
				cout<<"                                                                                 ";
			}
			
			if((t==63)&&(modo==0))//F5 para cargar solo en modo 0
			{
				gotoxy(1,23);
				cout<<"Introduce el nombre del archivo a cargar:";
				cin.getline(nombre,256);
				
				//por causa de un bug (error) del compilador no me permite
				//reusarla el mismo objeto ifstream para otro archivo,
				//probablemente la opci?n close() no funcione bien.
				//Para corregirlo se usa un truco, al poner un bloque de llaves
				//y declarar el objeto ent (tambi?n funciona con variables)
				//dentro de las mismas, cuando sale de las llaves destruye
				//el objeto, as? cuando vuelve a ingresar otra vez para cargar
				//un nuevo archivo, el objeto vuelve a crearse desde cero.
				
				{  //inicio bloque de llaves
					ifstream ent(nombre); //creamos el objeto para manejar entrada
					                      //de archivos llamado ent con el archivo
					                      // nombre
					m=0; //para contar la cantidad de l?neas
					
					do{
							ent.getline(cad,11);//leemos una linea del archivo ent y la colocamos en cad
							ancho=strlen(cad); //obtenemos longitud de cad
							memcpy(map[m],cad,ancho); //copiamos ancho caracteres
													  //memcpy es parecida a strncpy solo que no coloca el '\0'
							++m;
							if(m>9) break; //si superamos la cantidad de lineas que podemos almacenar terminamos la carga
						}while(!ent.eof()); //leemos hasta que el achivo se acabe
					alto=m;
					if(alto<1) alto=1; //si el archivo tiene lineas vacias acomodamos
					if(ancho<1) ancho=1;//alto y ancho
					px=py=0;//el cursor va a arriba a la izquierda
					//ent.close(); ya no se necesita porque ent se destruye al
				}   //llegar a esta llave
				
				clrscr(); //borramos la pantalla e imprimimos todo de nuevo
				imprdib(map,alto,ancho); //imprimimos la zona de dibujo
				imprmen(men,cx,cy); //imprimimos el men?
				imprayuda();//imprimimos las ayudas
			}
			
			gotoxy(py+2,px+2); //fijamos el cursor en su lugar
		}
		
	}
	
	return 0;
}


void imprdib(char map[][10],int alto,int ancho)
{
	int m,n;
	
	//dibujamos el area de dibujo
	
	gotoxy(1,1);
	cout<<(char)201;
	for(n=0;n<ancho;++n) cout<<(char)205;
	cout<<(char)187<<" ";
	for(m=0;m<alto;++m)
	{
		gotoxy(1,m+2);
		cout<<(char)186;
		for(int n=0;n<ancho;++n) cout<<map[m][n];
		cout<<(char)186<<" ";
	}
	gotoxy(1,m+2);
	cout<<(char)200;
	for(n=0;n<ancho;++n) cout<<(char)205;
	cout<<(char)188<<" ";
	gotoxy(1,m+3);
	cout<<"            ";
}

void imprmen(char men[][28],int cx,int cy)
{
	//el men? de chars
	int n,m;
	
	gotoxy(24,1);
	cout<<(char)218;
	for(n=0;n<27;n++) cout<<(char)196<<(char)194;
	cout<<(char)196<<(char)191;
	for(n=0;n<7;++n)
	{
		gotoxy(24,(n+1)*2);
		cout<<(char)179;
		for(m=0;m<28;++m) cout<<men[n][m]<<(char)179;
		gotoxy(24,(n+1)*2+1);
		cout<<(char)195;
		for(int o=0;o<27;o++) cout<<(char)196<<(char)197;
		cout<<(char)196<<(char)180;
	}
	gotoxy(24,16);
	cout<<(char)179;
	for(m=0;m<28;++m) cout<<men[7][m]<<(char)179;
	gotoxy(24,17);
	cout<<(char)192;
	for(int o=0;o<27;o++) cout<<(char)196<<(char)193;
	cout<<(char)196<<(char)217;
	ponecursor(men,cx,cy);
	
}

void quitacursor(char men[][28],int cx,int cy)
{
	// en donde se encuentra el cursor de men? imprimimos el caracter normal
	gotoxy(25+cy*2,cx*2+2);
	normvideo();
	cout<<men[cx][cy];
}

void ponecursor(char men[][28],int cx,int cy)
{
	//en donde se encuentra el cursor de men? imprimimos el caracter fondo blanco color negro
	gotoxy(25+cy*2,cx*2+2);
	textbackground(WHITE);
	textcolor(BLACK);
	cout<<men[cx][cy];
	normvideo(); //volvemos los colores a la normalidad para que las dem?s funciones impriman bien
}

void mensimple(void)
{
	//dibuja el recuadro del men? con lineas simple
	gotoxy(24,1);
	cout<<(char)218;
	for(int n=0;n<27;n++) cout<<(char)196<<(char)194;
	cout<<(char)196<<(char)191;
	for(int n=0;n<7;++n)
	{
		gotoxy(24,(n+1)*2);
		cout<<(char)179;
		gotoxy(80,(n+1)*2);
		cout<<(char)179;
		gotoxy(24,(n+1)*2+1);
		cout<<(char)195;
		gotoxy(80,(n+1)*2+1);
		cout<<(char)180;
	}
	gotoxy(24,16);
	cout<<(char)179;
	gotoxy(80,16);
	cout<<(char)179;
	gotoxy(24,17);
	cout<<(char)192;
	for(int n=0;n<27;n++) cout<<(char)196<<(char)193;
	cout<<(char)196<<(char)217;
}
	
void mendoble(void)
{
	//dibuja el recuadro del men? con lineas doble
	gotoxy(24,1);
	cout<<(char)201;
	for(int n=0;n<27;n++) cout<<(char)205<<(char)205;
	cout<<(char)205<<(char)187;
	for(int n=0;n<15;++n)
	{
		gotoxy(24,n+2);
		cout<<(char)186;
		gotoxy(80,n+2);
		cout<<(char)186;
	}
	gotoxy(24,17);
	cout<<(char)200;
	for(int n=0;n<27;n++) cout<<(char)205<<(char)205;
	cout<<(char)205<<(char)188;
}

void dibsimple(int ancho,int alto)
{
	//dibuja el recuadro del dibujo con linea simple
	gotoxy(1,1);
	cout<<(char)218;
	for(int n=0;n<ancho;++n) cout<<(char)196;
	cout<<(char)191;
	for(int n=0;n<alto;++n)
	{
		gotoxy(1,n+2);
		cout<<(char)179;
		gotoxy(ancho+2,n+2);
		cout<<(char)179;
	}
	gotoxy(1,alto+2);
	cout<<(char)192;
	for(int n=0;n<ancho;++n) cout<<(char)196;
	cout<<(char)217;
}

void dibdoble(int ancho,int alto)
{
	//dibuja el recuadro del dibujo con linea doble
	gotoxy(1,1);
	cout<<(char)201;
	for(int n=0;n<ancho;++n) cout<<(char)205;
	cout<<(char)187;
	for(int n=0;n<alto;++n)
	{
		gotoxy(1,n+2);
		cout<<(char)186;
		gotoxy(ancho+2,n+2);
		cout<<(char)186;
	}
	gotoxy(1,alto+2);
	cout<<(char)200;
	for(int n=0;n<ancho;++n) cout<<(char)205;
	cout<<(char)188;
}

void imprayuda(void)
{
	//imprimimos las ayudas
	gotoxy(1,19);
	cout<<"F2 Guardar Archivo  F5 Cargar Archivo  Enter cambiar tamano TAB Cambiar caracterEspacio dibujar caracter  Flechas mueven el cursor  Esc sale"; 
}
