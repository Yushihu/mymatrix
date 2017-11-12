CFLAGS+=-O3 -std=c99

all : smt_test

debug: 

ptest: main.o new_matrix.o
	gcc -o ptest main.o new_matrix.o -lm -lpthread $(CFLAGS)

smt_test: main.o mymatrix.o
	gcc -o smt_test main.o mymatrix.o -lm -g

main.o: main.c
	gcc -c main.c $(CFLAGS)

new_matrix.o: new_matrix.c
	gcc -c new_matrix.c $(CFLAGS)

mymatrix.o: mymatrix.c
	gcc -c mymatrix.c $(CFLAGS)


clean:
	rm -f main.o mymatrix.o smt_test new_matrix.o &> /dev/null