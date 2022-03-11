all :  test



test : test.o signature.o gestion_clef.o gestion_cryptage.o tests_primalite.o gestion_votants_candidats.o
	gcc -o test test.o signature.o gestion_clef.o gestion_cryptage.o tests_primalite.o gestion_votants_candidats.o


test.o : test.c signature.h gestion_clef.h ../Partie_1/gestion_cryptage.h ../Partie_1/tests_primalite.h gestion_votants_candidats.h
	gcc -c test.c



signature.o : signature.c ../Partie_1/gestion_cryptage.h gestion_clef.h
	gcc  -c signature.c  


gestion_cryptage.o : ../Partie_1/gestion_cryptage.c ../Partie_1/gestion_cryptage.h ../Partie_1/tests_primalite.h
	gcc -c ../Partie_1/gestion_cryptage.c

tests_primalite.o : ../Partie_1/tests_primalite.c ../Partie_1/tests_primalite.h
	gcc -c ../Partie_1/tests_primalite.c 


gestion_clef.o : gestion_clef.c ../Partie_1/tests_primalite.h
	gcc  -c gestion_clef.c 


gestion_votants_candidats.o : gestion_votants_candidats.c gestion_clef.h signature.h
	gcc -c gestion_votants_candidats.c

clean : 
	rm -f *.o test 
