FLAGS = -Wall -g



all: stringProg

stringProg: main.o
	gcc $(FLAGS) -o stringProg main.o
main.o: main.c
	gcc $(FLAGS) -c main.c

clean:
	rm -f *.o stringProg