pc: pc.c
	gcc -Wall -Wextra -o $@ $^ -lpthread

debug: pc.c
	gcc -g -Wall -Wextra -o $@ $^ -lpthread

.PHONY: clean

clean:
	rm -f pc debug
	rm -rf debug.dSYM
