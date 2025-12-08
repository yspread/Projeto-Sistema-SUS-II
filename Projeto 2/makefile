all: fila.o avl.o paciente.o procedimento.o historico.o
	gcc main.c fila.o avl.o paciente.o procedimento.o historico.o -o main -Wall -std=c99 -lm

clean:
	rm -f *.o *.zip *.bin main

run:
	./main

checkmem:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

fila.o: fila.c fila.h
	gcc -c fila.c -Wall -std=c99

paciente.o: paciente.c paciente.h historico.h
	gcc -c paciente.c -Wall -std=c99

avl.o: avl.c avl.h paciente.h
	gcc -c avl.c -Wall -std=c99

procedimento.o: procedimento.c procedimento.h
	gcc -c procedimento.c -Wall -std=c99

historico.o: historico.c historico.h procedimento.h
	gcc -c historico.c -Wall -std=c99