CC = gcc
DOSI: main.o
	$(CC)  -Wall -g3 -ggdb3 -o DOSI $^

main.o: main.c headers.h
	$(CC) -c $^

clean:
	rm *.o
	rm *.gch
