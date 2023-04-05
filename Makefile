CC = gcc
CFLAGS = -Wall -g

build: main

main: main.o operations.o my_operations.o
	$(CC) -o main $^ 

main.o: main.c
	$(CC) $(CFLAGS) -c $^

operations.o: operations.c
	$(CC) $(CFLAGS) -c $^

my_operations.o: my_operations.c
	$(CC) $(CFLAGS) -c $^

run: build
	./main sensors_clear_easy_1.dat
valgrind: 
	gcc -g main.c operations.c my_operations.c -o valg
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --vgdb=no ./valg sensors_clear_easy_1.dat
clean:
	rm -f *.o main