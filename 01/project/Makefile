CC=gcc
CCOPTS=-Wall -Wextra

hellothread: hellothread.c
	$(CC) $(CCOPTS) -o $@ $^

debug: hellothread.c
	$(CC) $(CCOPTS) -g -o $@ $^

clean:
	rm -f hellothread debug
	rm -rf debug.dSYM
