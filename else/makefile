
CC=gcc

CFLAGS = -I/usr/include
OBJECTS=mesa_example.o
OUTPUT=mesa_example
<<<<<<< HEAD
FLAGS_OPENGL = -lglut -lGL -lGLU 
LDFLAGS= ${FLAGS_OPENGL} 
=======

CFLAGS=-I/usr/local/Mesa-mesa-12.0.0-rc1.4/include -I/usr/include/GL
LDLIBS=-lX11 -lglut -lMesaGLU -lMesaGL -lm -lXext -lXmu
LDLIBS=-lX11 -lglut -lGLU -lGL -lm -lXext  
#-lXmu
LDFLAGS=-L/usr/local/mesa-12.0.0-rc1/lib -L/usr/include/X11/Xlib.h -L/usr/include/GL
>>>>>>> master

$(OUTPUT): $(OBJECTS)
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(OUTPUT) $(OBJECTS)

$(OBJECTS): mesa_example.h

clean:
	rm -f *.o
	rm -f mesa_example
