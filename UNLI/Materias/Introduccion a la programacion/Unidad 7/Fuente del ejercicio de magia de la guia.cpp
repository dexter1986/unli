#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

class magia{
      
      /* Elementos privados */
      
      private:              
              // atributos
              
              int mesa[7][3];  // presentacion de la mesa
              int mazo[21];    // el macito de 21 cartas
              
             // metodos
             
              void armar();    //arma por primera vez las columnas haciendo un random   
              void mostrar();  //muestra la mesa
              int ingresar(int veces);      //es el ingreso de la columna, tambien se encarga de mostrar la carta elegida
              void mezclar(int col);        //mezcla cada vez que se elige una columna
              void repartir();              //reparte el macito en la mesa, no muestra
              void mostrar_carta_elegida(int g);      //muestra la carta elegida
              
      /* Elementospublicos */
      
      public:
 
             magia();        //constructor, llama a "armar"
             void start();   //el unico metodo publico, es el que arranca el juego y organiza las manos
             ~magia();       // destructor, vacio
             
             
};      
        
        /***********************************/
        /* El constructor llama a armar, no lleva par?metro*/
        /*********************************/    
        
        magia::magia(){
           armar();
        }
        
        /***********************************/
        /* 
        m?todo: armar
        Arma la matriz de forma aleatoria
        primero pone los 21 valores ordenados y luego los cambia con alguna coordenada de forma aleatoria
        */
        /*********************************/
        
       void magia::armar(){
            srand (time(NULL));
           int c=1;
           
           for (int i=0;i<7;i++){
               for(int j=0;j<3;j++){
                  mesa[i][j]=c++;     
               }
           }
           
           for (int i=0;i<7;i++){
               for(int j=0;j<3;j++){
                  
                  int filaux=rand()%7;
                  int colaux=rand()%3;
                  int aux=mesa[i][j];
                  
                  mesa[i][j]=mesa[filaux][colaux];
                  mesa[filaux][colaux]=aux;     
               }
           }
           
       }

       /***********************************/
        /* 
        m?todo: mostrar
        Arma un peque?o entorno grafico para mostrar la mesa
        */
        /*********************************/

       void magia::mostrar(){
           
           cout<<endl<<endl;
           
           for (int i=0;i<7;i++){
               cout<<"|";
               for(int j=0;j<3;j++){
                  cout<<setw(5)<<mesa[i][j]<<" | ";     
               }
               cout<<endl;
           }
       cout<<endl<<setw(7)<<"col 1"<<setw(8)<<"col 2"<<setw(8)<<"col 3"<<endl;    
       cout<<endl;
       
       }        
      
        /***********************************/
        /* 
        m?todo: ingresar
        Pide la columna del espectador, recibe como parametro el nro de mano
        Devuelve la columna elegida
        */
        /*********************************/
      
      
       int magia::ingresar(int veces){
            
            int col=0;
            bool vale=false;
            
            while (!vale){
                  
                  cout<<endl<<"Ingrese el nro de columna en el cual esta su numero escogido (1-3): ";
                  cin>>col;
                  
                  if(col>0 && col<4)
                           vale=true;      
            }
            
            if (2-veces)
               cout<<endl<<"quedan "<<2-veces<<" elecciones"<<endl;
               
            else {
                 mostrar_carta_elegida(col-1);
                 return -1;
            }
            return col;
       
       }
      
        /***********************************/
        /* 
        m?todo: mezclar
        se encarga de mezclar poniendo la columna elegida en el medio
        */
        /*********************************/
      
      
       void magia::mezclar(int col){
            int fil=0;
            int col_selec[3];
            
            switch(col){
                        case 1: 
                             col_selec[0]=1;
                             col_selec[1]=0;
                             col_selec[2]=2;
                             break;
                        
                        case 2: 
                             col_selec[0]=0;
                             col_selec[1]=1;
                             col_selec[2]=2;
                             break;
                        
                        case 3: 
                             col_selec[0]=0;
                             col_selec[1]=2;
                             col_selec[2]=1;
                             break;
            }
            
            
            for(int j=0;j<3;j++){
                    for (int i=0;i<7;i++){     
                        mazo[fil]=mesa[i][col_selec[j]];
                        fil++;
                    }
            }       
       }
       
      
         /***********************************/
        /* 
        m?todo: repartir
        Acomoda el mazo en la mesa
        */
        /*********************************/
      
       void magia::repartir(){
            
            int fil=20;
            
            for(int i=0;i<7;i++){
                    for(int j=0;j<3;j++){
                          
                         mesa[i][j]=mazo[fil];
                         fil--;
                                                   
                    }        
            }

  
       }
      
      /*****************************/
      
      
      void magia::mostrar_carta_elegida(int g){
           
           
           
           cout<<endl<<"Ud eligio el: "<<mesa[3][g]<<endl<<endl;
           
           }
      
      
      /****************************/
      
      void magia::start(){
           
           
           
           for (int juego=0;juego < 3;juego++){
               mostrar();
               int c=ingresar(juego);    
               if (c>0){
                  mezclar(c);
                  repartir();
               }
           }     
      }
      
      
      
      
      // Declaracion del destructor        
              
      magia::~magia(){
           


        }
        
      
      
int main(int argc, char *argv[])
{
    
    magia M;
    M.start();
    
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
