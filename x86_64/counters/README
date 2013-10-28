This is going to be a place for microbenchmarking counters that, once
read, are assumed to be possibly stale, but which were accurate at
some point in the past.

## Mechanisms for Testing

* mutex-coordinated increment of shared counter

* lock prefix on add instruction (atomic increment) of shared
  counter

* atomic increment of non-shared counters

* regular increment of non-shared counters

## Quick Results

These are some lazy-fast runs done by the makefile's default target on
my MacBook pro with 2.26 Intel Core 2 Duo.  The mutex is expensive, as
expected.

  -*- mode: compilation; default-directory: "~/git/low/x86_64/counters/" -*-
  Compilation started at Sun Oct 27 21:05:53
  
  make 
  cc -g -Wall -o demo main.c -lpthread
  time sh -c './demo 10 400000 3; echo $?'
  10 threads for 400000 iterations, test type 3
  OK: resulting count is 4000000
  0
          0.02 real         0.01 user         0.00 sys
  time sh -c './demo 10 400000 2; echo $?'
  10 threads for 400000 iterations, test type 2
  OK: resulting count is 4000000
  0
          0.04 real         0.07 user         0.00 sys
  time sh -c './demo 10 400000 1; echo $?'
  10 threads for 400000 iterations, test type 1
  OK: resulting count is 4000000
  0
          0.08 real         0.14 user         0.00 sys
  time sh -c './demo 10 400000; echo $?'
  10 threads for 400000 iterations, test type 0
  OK: resulting count is 4000000
  0
         18.21 real         5.32 user        16.76 sys
  
  Compilation finished at Sun Oct 27 21:06:12

  
## Longer Runs

I'm not even going to try the mutex with big numbers of iterations,
but the other ones look like this on my MacBook Pro with 2.26 GHz
Intel Core 2 Duo.

Using per-thread atomic increment takes roughly four times as long as
using increment without locking the memory bus.  This is the key
observation I was interested in.

### Regular increment of non-shared counters

  ecashin@Ed-Cashins-MacBook-Pro counters$ time ./demo 10 40000000 3
  10 threads for 40000000 iterations, test type 3
  OK: resulting count is 400000000
  
  real    0m0.932s
  user    0m1.720s
  sys     0m0.011s

### Atomic increment (add with lock prefix) of non-shared counter

  ecashin@Ed-Cashins-MacBook-Pro counters$ time ./demo 10 40000000 2
  10 threads for 40000000 iterations, test type 2
  OK: resulting count is 400000000
  
  real    0m4.206s
  user    0m7.661s
  sys     0m0.037s

### Atomic with shared counter

  ecashin@Ed-Cashins-MacBook-Pro counters$ time ./demo 10 40000000 1
  10 threads for 40000000 iterations, test type 1
  OK: resulting count is 400000000
  
  real    0m8.164s
  user    0m15.234s
  sys     0m0.066s
  ecashin@Ed-Cashins-MacBook-Pro counters$ 
