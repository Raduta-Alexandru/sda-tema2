build:
	gcc -Wall -Werror main.c funcSat.c funcHeap.c funcArb.c funcPQ.c funcAux.c -o tema2

run:
	./tema2

clean:
	rm tema2