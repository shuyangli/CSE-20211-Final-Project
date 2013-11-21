all: sudoku

sudoku: main.o gfx.o drawCharacters.o drawNumeral.o
	gcc main.o gfx.o drawCharacters.o drawNumeral.o -o sudoku -lX11 -lm

main.o: main.c
	gcc -c main.c -lm

gfx.o: gfx.c
	gcc -c gfx.c -lX11 -lm

drawCharacters.o: drawCharacters.c
	gcc -c drawCharacters.c -lm

drawNumeral.o: drawNumeral.c
	gcc -c drawNumeral.c -lm

drawTest: drawTest.c
	gcc drawTest.c gfx.c drawNumeral.c drawCharacters.c -o drawTest -I/usr/X11R6/include -L/usr/X11R6/lib -lX11 -lm

clean:
	rm *.o