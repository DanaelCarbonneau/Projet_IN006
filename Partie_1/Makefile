all : main 


main : main.o tests_primalite.o
	gcc -o main main.o tests_primalite.o -lm

tests_primalite.o : tests_primalite.c tests_primalite.h
	gcc -c tests_primalite.c 

main.o : main.c tests_primalite.h
	gcc -c main.c


clean : 
	rm -f *.o main 