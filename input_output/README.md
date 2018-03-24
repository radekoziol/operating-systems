# input_output

C project that compares system and library functions for input_output.
Program perform time measurment of sorting file and copying files that's output is in report.txt

## Getting Started

``` 
usage:
Arguments are: 
 -generate      path num1 num2
 -sort          path num1 num2 how
 -copy          path1 path2 num1 num2 how
Description: 
 -generate  -  generates <num1> lines of data with strings  of length <num2> to file <path> 
 -sort      -  sorts given file <path> that contains  <num1> lines of string of length <num2>. It can be done with library functions <how = 'lib'> or system functions <how = 'sys>.
 -copy      -  copies <num1> lines of string of length <num2> to file <path1>. It can be done with library functions <how = 'lib'> or system functions <how = 'sys>.
```

### Conclusions

After performing some longer test (result.txt): <br />
Let x = records_number/records_length , then: <br />
* as x is big (512/4) library functions perform much faster (10 times) <br />
* as x is small (85/8192) system functions perform a bit faster (1.5 times) <br />

Method read() do not do buffering, therefore read() 1 byte at a time will make huge performance penalty 
compared to doing the same thing with fread(). <br />
Method fread() will pull a block and dole it out as you ask for it. <br />
Method read() will drop to the kernel for each call.<br />
