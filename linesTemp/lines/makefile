
CC = gcc

SOURCE= lines.c
OUTPUT=lines
OBJECT=lines.o
LDFLAGS= -lSDL_bgi -lSDL2 -lgraph -lm
CFLAGS = -I/usr/include/


$(OUTPUT): $(OBJECT)
	$(CC) $(OBJECT) -o $(OUTPUT) $(LDFLAGS) $(CFLAGS) 

$(OBJECT): $(SOURCE)
	$(CC) -c $(SOURCE) -o lines.o $(LDFLAGS)

clean:
	rm -f *.o
	rm -f lines
