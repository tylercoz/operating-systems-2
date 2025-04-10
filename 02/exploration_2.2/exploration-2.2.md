<!-- Exploration 2.2: Locking Data Structures -->

Data structures don't tend to work when used with multiple threads due
to numerous race conditions within them.

Even a simple loop with a shared variable can't handle multiple threads
running over it at the same time.

So to make things work, you need to:

1. Identify the critical sections
2. Carefully wrap them in locks

Make sure that the time the data structure spends locked is as short as
possible. (Remember that the locks prevent other threads from running.)

If possible, don't lock the entire data structure. Some data structures
allow you to lock just part of the structure for better performance.
(See the queue example in the book.)

> Fun Fact: SQLite uses one big lock on an entire database when anyone
> wants to change it. This blocks other threads from changing anything
> at the same time even if the changes are in completely separate
> tables.
>
> This fits with SQLite's design philosophy which typically only has one
> thread using it.
>
> Other databases lock individual tables, and some lock down to the
> individual row level.

If a data structure locks large sections of itself when being updated,
we call that locking _coarse-grained_.

If it locks only the smallest section of itself necessary to complete an
operation, we call those locks _fine-grained_.

## Eventual Consistency

In databases, there's a term _eventual consistency_. This is the idea
that maybe two views of the world aren't consistent right now (e.g.
maybe a showtime for a movie has been updated, but one client sees the
old time and another client sees the new time).

But _eventually_ both will see the new time.

Strictly locking data structures means that all users of that structure
will have the same, consistent view of that data.

However, some data structures are amenable to having a temporarily
inconsistent view between different threads. (See the Approximate
Counter example in the book.)

## Non-Blocking/Lock-free Algorithms

There are a few algorithms that don't rely on mutexes to be concurrent.
They use primitives mentioned earlier like Compare-and-Swap or
Test-and-Set to get the job done.

As [Herb Sutter](https://en.wikipedia.org/wiki/Herb_Sutter) said, a new
lock-free algorithm is a publishable result. These things are rare and
hard to come up with, and hard to understand. You can take a quick peek
at a [non-blocking linked
list](https://en.wikipedia.org/wiki/Non-blocking_linked_list) on
Wikipedia for an idea of how it works.

## Reflect

* What are the tradeoffs with the Approximate Counter in the book when
  updating the global counter more or less frequently?

The more frequently you update it, the less performant / scalable it will be.

The less frequently you update it, the less accurate the global counter will be.

* Why does having locks on both the head and tail of the concurrent
  queue have a performance advantage over having one big lock for the
  whole thing?

Having locks on both the head and tail of the queue will be more performant because it allows for concurrent access to the head and tail of the queue without blocking other threads from accessing the other end of the queue. You won't run into issues because the head and end are independent and don't interact with each other, assuming the queue's size is greater than one.

* Why doesn't the concurrent hash table in the reading need any locks in
  any of the `Hash_` functions?

Because concurrency is handled in the underlying `List_` functions, which are what handle the buckets.

* In the [concurrent queue in the
  book](https://pages.cs.wisc.edu/~remzi/OSTEP/threads-locks-usage.pdf),
  speculate on why the dummy node is required.

So that the head and tail are never the same node, preventing two threads accessing the same resource.
