CC = gcc

all: my_library.o 
	${CC} -c main.c
	${CC} -o main.out main.o my_library.o

my_library.o: libs/my_library.c 
	${CC} -c libs/my_library.c

clean:
	rm *.o
	rm *.out