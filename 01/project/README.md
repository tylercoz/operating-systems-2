# Multithreading

## Building

Command line:

* `make` to build. An executable called `hellothread` will be produced.
* `make debug` to debug. An executable called `debug` and a symbol directory `debug.dSYM` will be produced. Can use `lldb` or `gdb` to debug.
* `make clean` will delete all executables and symbol directories.

## Files

* `hellothread.c`: Makes multiple threads that print 0-4 to the command line. Has a sleep in the middle to show concurrency.

## Data

used pthread_t type for threads.

## Functions

* `main()` - prints beginning and ending message, creates and joins the threads
* `run()` - thread function, prints thread number and numbers 0-4

## Notes

* `usleep(10000)` in `run()` can be removed, it's just to show concurrency.
