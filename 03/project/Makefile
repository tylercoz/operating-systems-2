FLAGS = -Wall -Wextra -Werror

pc: pc.c eventbuf.c
	gcc $(FLAGS) -o $@ $^

debug: pc.c eventbuf.c
	gcc -g -Wall -Wextra -o $@ $^ -lpthread

.PHONY: clean

clean:
	rm -f pc debug
	rm -rf debug.dSYM
