# semaphores
Demonstration of barbershop implemented with IPC and semaphores in POSIX or SYSTEM V.

## Getting Started
Barber (server.c) has limited seats number <seats_num>. <br />
Client (client.c) creates <client_num> clients. Each visits barber <visit_num> to get his hair cut. 

Barber (server.c)
``` 
Arguments are: 
    seats_num 
```
Client (client.c)
``` 
Arguments are: 
    client_num visit_num
```
