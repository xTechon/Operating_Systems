# Banker's Algorithm Tester
## Dependencies
If you are on Linux, install eigen and fmt from your package manager

If you are on windows, follow their install guides:

https://eigen.tuxfamily.org/

https://fmt.dev/

## Build
Make a directory called `cmake-build-debug`

Run `cmake -Bcmake-build-debug -S. && cmake --build cmake-build-debug` 

in project root

## Run
Simply type `./BankersAlgo [StateFilePath]`
or          `./BankersAlgo [StateFilePath] [RequestFilePath]`
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
1,9,5
4,3,0
3,0,6
1,5,5
4,12,4
4,7,6
7,5,9
```

p.s. the line endings must be `\n` and not `\n\r`

## Request Format 
To Batch test Requests Sequentially for a specific state, use another `.csv` but of this format:

```
number of Requests
ProcID, Request Vector
ProcID, Request Vector
ProcID, Request Vector
ProcID, Request Vector
```
e.g:

```
2
2,0,1,1
0,1,1,1
```

Declare how many requests are in the file followed by each request. Each line is a new seperate request, and the user will be prompted if they want to test each request against the original state or test the sequence of grating requests for a safe state.

## Notes:
Please don't run the request options when requests don't exist yet

Make sure the line endings are in `\n` and not `\n\r` for the request file also
