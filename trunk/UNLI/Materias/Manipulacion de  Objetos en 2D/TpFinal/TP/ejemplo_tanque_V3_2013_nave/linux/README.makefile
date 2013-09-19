CG:                                                                   2006/08/08

== El formato del archivo Makefile ==

Un archivo Makefile es un archivo de texto en el cual se distinguen cuatro tipos
básicos de declaraciones:

    * Comentarios.
    * Variables.
    * Reglas explícitas.
    * Reglas implícitas. 

== Comentarios ==

Al igual que en los programas, contribuyen a un mejor entendimiento de las 
reglas definidas en el archivo. Los comentarios se inician con el caracter #, 
y se ignora todo lo que continúe después de ella, hasta el final de línea.

	# Este es un comentario
			

== Variables ==

Se definen utilizando el siguiente formato:

        nombre = dato
			

De esta forma, se simplifica el uso de los archivos Makefile. Para obtener el 
valor se emplea la variable encerrada entre paréntesis y con el caracter $ al 
inicio, en este caso todas las instancias de $(nombre) serán reemplazadas por 
dato. Por ejemplo, la siguiente definición

        SRC = main.c
			

origina la siguiente línea:

        gcc $(SRC)
			

y será interpretada como:

        gcc main.c
			

Sin embargo, pueden contener más de un elemento dato. Por ejemplo:

        objects = programa_1.o programa_2.o programa_3.o \
                  programa_4.o programa_5.o

        programa: $(objects)
                  gcc -o programa $(objects)
			

Hay que notar que make hace distinción entre mayúsculas y minúsculas.

== Reglas explícitas ==

Estas le indican a make qué archivos dependen de otros archivos, así como los 
comandos requeridos para compilar un archivo en particular. Su formato es:

        archivoDestino: archivosOrigen
               comandos  

NOTA: Existe una caracter TAB (tabulador) antes de cada comando.
			

Esta regla indica que, para crear archivoDestino, make debe ejecutar comandos 
sobre los archivos archivosOrigen. Por ejemplo:

        main: main.c funciones.h
              gcc -o main main.c funciones.h
			

significa que, para crear el archivo de destino main, deben existir los archivos
main.c y funciones.h y que, para crearlo, debe ejecutar el comando:

        gcc -o main main.c funciones.h
			

== Reglas implícitas ==

Son similares a las reglas explícitas, pero no indican los comandos a ejecutar,
sino que make utiliza los sufijos (extensiones de los archivos) para determinar
que comandos ejecutar. Por ejemplo:

        funciones.o: funciones.c funciones.h
			

origina la siguiente línea:

        $(CC) $(CFLAGS) -c funciones.c funciones.h
			

Existe un conjunto de variables que se emplean para las reglas implícitas, y 
existen dos categorías: aquellas que son nombres de programas (como CC) y 
aquellas que tienen los argumentos para los programas (como CFLAGS). Estas 
variables son provistas y contienen valores predeterminados, sin embargo, pueden
ser modificadas, como se muestra a continuación:

        CC = gcc
		CFLAGS = -Wall -O2
			

En el primer caso, se ha indicado que el compilador que se empleará es gcc y 
sus parámetros son -Wall -O2


Bibliografia:
[1] http://www-gris.det.uvigo.es/~belen/pem/apuntes/node13.html
[2] http://www.ubiobio.cl/~gpoo/documentos/make/makefile.html
