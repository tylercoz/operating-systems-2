# Mutexes

## Building

Command line:

* `make` to build. An executable called `reservations` will be produced.
* `make debug` to debug. An executable called `debug` and a symbol directory `debug.dSYM` will be produced. Can use `lldb` or `gdb` to debug.
* `make clean` will delete all executables and symbol directories.

## Files

* `reservations.c`: initializes brokers, runs the brokers (free, reserve, verify) and completes brokers.

## Data

* Global array holding seat_taken data
* a mutex lock on all functions that access the global array

## Functions

* `is_free(int n)`: returns true if given seat is available
* `reserve_seat(int n)`: reserve given seat and return 0 if seat was free, else return -1
* `free_seat(int n)`: free given seat and return 0 if seat was reserved, else return -1
* `verify_seat_count(void)`: manually count all taken seats and check running count to ensure threads haven't overlapped.
* `seat_broker(void *arg)`: randomly reserves and free's seats transaction_count times. Verifies that the running seat_taken count is still true, returns NULL if not.

## Notes

* Class assignment to add mutex locks to prevent race conditions.
