CC= gcc
CFLAGS= -Wall -Wextra -Werror
LDFLAGS= -lSDL2 -lSDL2_image `sdl2-config --cflags --libs`

main:
	$(CC) -o pong *.c $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm pong
