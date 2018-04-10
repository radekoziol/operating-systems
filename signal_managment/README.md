# signal_managment
3 programs connected with signals. 
## Getting Started
### ex1
```
Run without arguments. Then use CTRL+Z or CTRL+C  
```
### ex2 
Creates <child_number> children processes, then each ask parent to start work.
After receiving <request_number> requests, parent allows them and every other children asking since then. 
``` 
Arguments are: 
  child_number request_number
```
### ex3
Creates child process, which get's <signal_number> signals from parent and then signal to stop work.
Type 1,3 specify what signals are sent SIGUSR1, SIGUSR2 or real time signals.
Type 2 makes parent wait for response from each sent signal to child.
``` 
Arguments are: 
  signal_number type={1,2,3}
```
