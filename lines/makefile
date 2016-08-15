CC=gcc

SOURCE= pro0.c
OUTPUT=pro0
OBJECT=pro0.o
LDFLAGS= -lglut -lGL -lGLU -lm
CFLAGS = -I/usr/include/GL


$(OUTPUT): $(OBJECT)
	$(CC) $(OBJECT) -o $(OUTPUT) $(LDFLAGS) $(CFLAGS) 

$(OBJECT): $(SOURCE)
	$(CC) -c $(SOURCE) -O pro.o $(LDFLAGS)

clean:
	rm -f *.o
	rm -f pro0
