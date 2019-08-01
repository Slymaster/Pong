CC= gcc
CFLAGS= -Wall -Wextra -Werror
LDFLAGS= sdl2-config --cflags --libs

main:
	$(CC) -o pong *.c $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm pong
