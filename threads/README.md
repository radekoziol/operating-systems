# threads
2 programs connected with threads. 
## Getting Started

Program that filters given <in_img> image (extension ascii.pgm) using <th_num> threads with given
filter matrix <filter_path> (or randomly generated if filter_path is not present). out_img specifies 
output image to be overwritten. test option performs measurments (check report.txt) of speed in perfoming 
filtering with diffrent number of threads. 

### ex1
```
Arguments are: 
    th_num in_img filter_path(opt) out_img
    test
```
