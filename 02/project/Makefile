reservations: reservations.c
	gcc -Wall -Wextra -o $@ $^ -lpthread

reservations.zip:
	rm -f $@
	zip $@ Makefile reservations.c

debug: reservations.c
	gcc -g -Wall -Wextra -o $@ $^ -lpthread

.PHONY: clean

clean:
	rm -f reservations debug
	rm -rf debug.dSYM
