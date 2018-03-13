CC=gcc
CFLAGS=-Wall

main_0: main.o
	$(CC) $(CFLAGS) -o -c main main.c

main_1: main.o
	$(CC) $(CFLAGS) -o1 -c main main.c

main_2: main.o
	$(CC) $(CFLAGS) -o2 -c main main.c

main_3: main.o
	$(CC) $(CFLAGS) -o3 -c main main.c

main_s: main.o
	$(CC) $(CFLAGS) -os -c main main.c

main_with_staticlib: 
	cc -o main main.c "./library (ex 1)/libstatic_lib.a" 

main_with_sharedlib:
	$(CC) -L. -l:-L. -l:"./library (ex 1)/libmy_lib.so".so

main_with_dynamiclib:
	$(CC) $(CFLAG) -I/main.c -L/"./library (ex 1)/libmy_lib.so" main.c -lctest -o main

