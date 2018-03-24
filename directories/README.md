# directories

C project that implements 'ls -l' like command, using nftw method or system methods with one possible condition
(time modification)

## Getting Started

``` 
usage:
Arguments are: 
   path condition date (how)
Description: 
 Possible conditions: 
  '>' modified later than <date> 
  '=' modified at the same <date> 
  '<' modified earlier than <date> 
 Path must be in format day mm//dd/yy hh:mm:ss AM/PM f.e 'Tue 10/30/2001 10:59:10 AM'
 <how = 'sys'> (default) uses methods like opendir, ..
 <how = 'nftw' uses method nftw
```
