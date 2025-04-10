CC=gcc
CCOPTS=-Wall -Wextra

reservations: reservations.c
	$(CC) $(CCOPTS) -o $@ $^

debug: reservations.c
	$(CC) $(CCOPTS) -g -o $@ $^

clean:
	rm -f reservations debug
	rm -rf debug.dSYM
