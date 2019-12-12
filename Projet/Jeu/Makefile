CC = gcc
CFLAGS = -W -Wall -ansi -std=c99 -g `sdl2-config --cflags`
# LIBS = -L./SDL2_ttf/.libs
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf
# INCLUDES = -I./SDL2_ttf
INCLUDES = 
EXEC = main
SRC = main.c jeu.c
OBJ = $(SRC:.c=.o)

all: $(EXEC)

main: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf *.o *~

mrproper: clean
	rm -rf $(EXEC)
