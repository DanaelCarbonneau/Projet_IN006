all : test_SHA256

test_SHA256 : test_SHA256.c
	gcc -o test_SHA256 test_SHA256.c -lssl -lcrypto
	
block.o : block.c block.h
	gcc -c block.c

test : test.o block.o gestion_clef.o chaine_protected.o
	gcc -o test test.o block.o gestion_clef.o chaine_protected.o

test.o : test.c ../Partie_2/gestion_clef.h ../Partie_3/chaine_protected.h
	gcc -c test.c

#Fichiers des parties précédentes

gestion_clef.o : ../Partie_2/gestion_clef.c ../Partie_1/tests_primalite.h
	gcc  -c ../Partie_2/gestion_clef.c

chaine_protected.o : ../Parie_3/chaine_protected.c ../Partie_3/chaine_protected.h ../Partie_2/signature.h
	gcc -c chaine_protected.c

clean : rm *.o test_SHA256
