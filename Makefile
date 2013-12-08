all: sudoku

LINF = -lX11 -lm
MACF = -I/usr/X11R6/include -L/usr/X11R6/lib

sudoku: main.c gfx.o drawCharacters.o
	gcc main.c gfx.o drawCharacters.o -o sudoku $(MACF) $(LINF)

gfx.o: gfx.c
	gcc -c gfx.c $(MACF) $(LINF)

drawCharacters.o: drawCharacters.c
	gcc -c drawCharacters.c $(MACF) $(LINF)

clean:
	rm *.o