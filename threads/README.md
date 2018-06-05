# threads
2 programs connected with threads. 
## Getting Started

### ex1

Program that filters given <in_img> image (extension ascii.pgm) using <th_num> threads with given
filter matrix <filter_path> (or randomly generated if filter_path is not present). out_img specifies 
output image to be overwritten. test option performs measurements (check report.txt) of speed in performing
filtering with different number of threads.

```
Arguments are: 
    th_num in_img filter_path(opt) out_img
    test
```

### ex2

Program solves the producer–consumer problem (also known as the bounded-buffer problem)
using either semaphores or mutex'es.
The problem describes two processes, the producer and the consumer, who share a common,
fixed-size buffer used as a queue.
Producer posts strings to buffer. Client read them and print if their length is
<comparator [=,>,<] > than fix_len. Program will run for max_time(sec) or ,if max_time = 0,
till whole text is read.

```
Arguments are:
    <prod_num> <cl_num> <buf_size> <fix_len> <comparator> <print_more> <max_time>");
```
