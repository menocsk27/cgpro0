Tecnológico de Costa Rica
 IC8019 - Gráficos Por Computadora, PROYECTO 0: Algoritmos de líneas


 Profesor: Dr. Francisco Torres Rojas
 Estudiantes:
	Carlos Girón Alas
	Julián J. Méndez Oconitrillo
	Daniel Troyo Garro

Archivos dados:
	lines.c
	lines.o
	lines
	SDL_bgi-2.0.6.tar.gz
	libgraph-1.0.2.tar.gz
	makefile
	README.txt


Librerías utilizadas: SDL_bgi y SDL_2, junto con <graphics.h>



Para ejecutar el programa, debe instalar ciertos paquetes con anterioridad. 
Ejecute los siguientes comandos para instalarlos.

	sudo apt-get install build-essential
	sudo apt-get install libsdl2-dev

	sudo apt-get install libsdl-image1.2 libsdl-image1.2-dev guile-1.8   guile-1.8-dev libsdl1.2debian libart-2.0-dev libaudiofile-dev   libesd0-dev libdirectfb-dev libdirectfb-extra libfreetype6-dev   libxext-dev x11proto-xext-dev libfreetype6 libaa1 libaa1-dev   libslang2-dev libasound2 libasound2-dev

Tras realizar esto extraiga el proyecto y diríjase a la ruta de extracción:

	cd path/to/extracted/folder/lines/ 


Extraer libgraph-1.0.2.tar.gz y ejecutar 

	cd path/to/extracted/folder/libgraph-1.0.2

Ejecutar estos comandos

	./configure
	make
	sudo make install
	sudo cp /usr/local/lib/libgraph.* /usr/lib


Extraer SDL_bgi-2.0.6.tar.gz y ejecutar 

	cd path/to/extracted/folder/SDL_bgi-2.0.6

Ejecutar estos comandos

	cd src
	make
	sudo make install

Ejecute el makefile.

	make

Ejecute el programa.

	./lines <res> <# lineas> <veces>

<res> : Entero que indica la resolución de la pantalla cuadrada sobre la cual se dibujarán las lineas.
<# lineas> : Entero que indica el número de líneas a ser dibujadas en la pantalla por cada algoritmo.
<# veces> : Entero que indica el número de veces a dibujar una línea por cada algoritmo.

El programa requiere los tres parámetros, de lo contrario mostrará error. 