# Producers and Consumers

## Building

Command line:

* `make` to build. An executable called `reservations` will be produced.
* `make debug` to debug. An executable called `debug` and a symbol directory `debug.dSYM` will be produced. Can use `lldb` or `gdb` to debug.
* `make clean` will delete all executables and symbol directories.

## Files

* `pc.c`:
  * Creates and joins producer and consumer threads to handle tasks.
* `eventbuf.c`:
  * Queue data structure.

## Data

* `pc.c`:
  * `eventbuf` holds events. Shared between producer and consumer threads.

## Functions

* `pc.c`:

  * `sem_open_temp()`: Handles opening, unlinking and closing semaphores.

  * `producer_event_number()`: Combines producer number with event number to output unique identifying number for tasks in the event buffer.

  * `produce()`: Concurrent thread function for adding events to the event buffer.

  * `consume()`: Concurrent thread function for removing events from the event buffer.

  * `main()`: Creates global event buffer, creates producer and consumer threads and cleans up event buffer, producer and consumer threads.

* `eventbuf.c`:

  * `eventbuf_create()`: make a new eventbuf

  * `eventbuf_free()`: free previously-created eventbuf

  * `eventbuf_add()`: add an event to the eventbuf

  * `eventbuf_get()`: remove an event to the eventbuf

  * `eventbuf_empty()`: true if there are no items in the eventbuf

## Notes

* `pc.c`
  * Waiting for event_buffer to be empty before cancelling consumer threads needs to be refactored. Currently unoptimal.
