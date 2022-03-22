all : test

test : test.o chaine_cle.o
	gcc -o test test.o chaine_cle.o

test.o : test.c chaine_cle.h
	gcc -c test.c

chaine_cle.o : chaine_cle.c chaine_cle.h ../Partie_2/gestion_clef.h
	gcc -c chaine_cle.c
