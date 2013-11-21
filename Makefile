all: sudoku

sudoku: main.o gfx.o drawCharacters.o drawNumeral.o
	gcc main.o gfx.o drawCharacters.o drawNumeral.o -o sudoku

main.o: main.c
	gcc -c main.c

gfx.o: gfx.c
	gcc -c gfx.c

drawCharacters.o: drawCharacters.c
	gcc -c drawCharacters.c

drawNumeral.o: drawNumeral.c
	gcc -c drawNumeral.c

clean:
	rm *.o