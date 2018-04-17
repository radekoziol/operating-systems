# signal_managment
2 programs connected with pipes. 

## Getting Started
### ex1

C project that executes unix commands stored in file(1st arg) with some time(s) and memory limit(MB).
It works just like batch operting system - every command is executed in diffrent process. It is the same as
in process_managment project but now it supports pipes
```
Arguments are: 
  path time_limit memory_limit
Commands should be in seperated lines, f.e check file.txt
```

### ex2 
Demonstration of two programs master and slave communicating with each other. 
Slave is sending N messages to master. 
(it's pid and date) 
``` 
Run master.c <path_to_pipe> 
then slave.c <path_to_pipe> <N>
```
