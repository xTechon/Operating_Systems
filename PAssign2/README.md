# Banker's Algorithm Tester
---
## Build
Make a directory called `cmake-build-debug`

Run `cmake -Bcmake-build-debug -S. && cmake --build cmake-build-debug` 

in project root

## Run
Simply type `./BankersAlgo [FilePath]`

or run `./BankersAlgo` to type a file path

## Input Format
Pass the program a `.csv` file in this format:
```
numResource,numProccess
Available vector of size numResource: 0,1,...,numResource
Allocations rows:
0,1,...,numResource
.
.
.
numProccess
Max Rows:
0,1,...,numResource
.
.
.
numProccess
```
e.g.:

```
3,3
1,2,5
4,3,0
3,0,6
1,5,5
3,12,4
4,7,3
7,3,9
```

p.s. the line endings must be `\n` and not `\n\r`
