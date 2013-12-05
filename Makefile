all: sudoku

$(LIN_F) = -lX11 -lm

sudoku: main.c gfx.o drawCharacters.o
	gcc main.c gfx.o drawCharacters.o -o sudoku $(LIN_F)

gfx.o: gfx.c
	gcc -c gfx.c $(LIN_F)

drawCharacters.o: drawCharacters.c
	gcc -c drawCharacters.c $(LIN_F)

clean:
	rm *.o