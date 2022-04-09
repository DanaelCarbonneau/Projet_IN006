all : test test_SHA256

test_SHA256 : test_SHA256.c
	gcc -o test_SHA256 test_SHA256.c -lssl -lcrypto
	
block.o : block.c block.h ../Partie_3/chaine_protected.h ../Partie_2/signature.h ../Partie_2/gestion_clef.h
	gcc -c block.c -lssl -lcrypto

test : test.o block.o gestion_clef.o chaine_protected.o signature.o tests_primalite.o gestion_cryptage.o
	gcc -o test test.o block.o gestion_clef.o chaine_protected.o signature.o tests_primalite.o gestion_cryptage.o -lssl -lcrypto

test.o : test.c ../Partie_2/gestion_clef.h ../Partie_3/chaine_protected.h
	gcc -c test.c

#Fichiers des parties précédentes

gestion_clef.o : ../Partie_2/gestion_clef.c ../Partie_1/tests_primalite.h 
	gcc  -c ../Partie_2/gestion_clef.c

chaine_protected.o : ../Partie_3/chaine_protected.c ../Partie_3/chaine_protected.h ../Partie_2/signature.h
	gcc -c ../Partie_3/chaine_protected.c


signature.o : ../Partie_2/signature.c ../Partie_1/gestion_cryptage.h ../Partie_2/gestion_clef.h
	gcc  -c ../Partie_2/signature.c 

gestion_cryptage.o : ../Partie_1/gestion_cryptage.c ../Partie_1/gestion_cryptage.h ../Partie_1/tests_primalite.h
	gcc -c ../Partie_1/gestion_cryptage.c

tests_primalite.o : ../Partie_1/tests_primalite.c ../Partie_1/tests_primalite.h
	gcc -c ../Partie_1/tests_primalite.c 
	

clean:
	rm -f *.o test test_SHA256
