CC=gcc
CFLAGS=-Wall

server: server.o
	$(CC) $(CFLAGS) -o server server.c -pthread -lrt

client: client.o
	$(CC) $(CFLAGS) -o client client.c -pthread -lrt

