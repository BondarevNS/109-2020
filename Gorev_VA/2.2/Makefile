all: do-test clear

do-test: a.out
	./a.out

a.out: file.o trap_sum.o
	gcc -c trap_sum.c
	gcc -c trap_sum.c
	gcc trap_sum.o file.o

clear:
	rm trap_sum.o file.o a.out