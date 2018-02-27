# Makefile para Computacion Grafica

LDIR	 = -L./SDL/
IDIR	 = -I./SDL/include/
CFLAGS = -Wall -O3 -g
CC		 = tcc
OUTPUT = q1
SRC    = q1.c bitmap.c kool_aid.c matrix.c -lm

all:
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SRC)

run: all
	./$(OUTPUT)

clean:
	rm -f $(OUTPUT) *.bmp *.o *.o

love:
	@echo "Not war?"
