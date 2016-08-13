
CC=gcc

CFLAGS = -I/usr/include
OBJECTS=mesa_example.o
OUTPUT=mesa_example
FLAGS_OPENGL = -lglut -lGL -lGLU 
LDFLAGS= ${FLAGS_OPENGL} 

$(OUTPUT): $(OBJECTS)
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(OUTPUT) $(OBJECTS)

$(OBJECTS): mesa_example.h

clean:
	rm -f *.o
	rm -f mesa_example
