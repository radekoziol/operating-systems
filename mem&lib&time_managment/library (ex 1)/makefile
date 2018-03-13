CC=gcc
CFLAGS=-Wall

main: main.o
	$(CC) $(CFLAGS) -o main main.c.

static_lib: 
	$(CC) -c block_arrays_dynamically.c block_arrays_statically.c
	ar rcs libstatic_lib.a block_arrays_dynamically.o block_arrays_statically.o
	ranlib libstatic_lib.a

shared_lib:
	$(CC) -fPIC -c block_arrays_dynamically.c
	$(CC) -fPIC -c block_arrays_statically.c
	$(CC) -shared -o libmylib.so block_arrays_dynamically.o block_arrays_statically.o




