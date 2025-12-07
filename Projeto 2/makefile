all:fila.o avl.o paciente.o IO.o
	gcc main.c fila.o avl.o paciente.o -o main -Wall -std=c99 -pedantic-errors 

clean:
	rm -f *.o *.zip *.bin main

run:
	./main

checkmem:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

IO.o:
	gcc -c IO.c

fila.o:
	gcc -c fila.c

paciente.o:
	gcc -c paciente.c

avl.o:
	gcc -c avl.c