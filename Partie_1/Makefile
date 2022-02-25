all :  main_cryptage main

main : main.o tests_primalite.o
	gcc -o main main.o tests_primalite.o -lm

main_cryptage : main_cryptage.o tests_primalite.o gestion_cryptage.o
	gcc -o main_cryptage main_cryptage.o tests_primalite.o gestion_cryptage.o -lm

gestion_cryptage.o : gestion_cryptage.c gestion_cryptage.h tests_primalite.h
	gcc -c gestion_cryptage.c

main_cryptage.o : main_cryptage.c tests_primalite.h gestion_cryptage.h
	gcc -c main_cryptage.c

tests_primalite.o : tests_primalite.c tests_primalite.h
	gcc -c tests_primalite.c 

main.o : main.c tests_primalite.h
	gcc -c main.c


clean : 
	rm -f *.o main main_cryptage