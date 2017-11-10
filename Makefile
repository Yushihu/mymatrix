all : smt_test
smt_test: main.o mymatrix.o
	gcc -o smt_test main.o mymatrix.o -lm -g

main.o: main.c
	gcc -c main.c -g

mymatrix.o: mymatrix.c
	gcc -c mymatrix.c -g

clean:
	rm -f main.o mymatrix.o smt_test &> /dev/null