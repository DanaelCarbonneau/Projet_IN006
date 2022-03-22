all : test

#Compilation de la partie

test : test.o chaine_cle.o	signature.o gestion_clef.o gestion_cryptage.o tests_primalite.o
	gcc -o test test.o chaine_cle.o signature.o gestion_clef.o gestion_cryptage.o tests_primalite.o

test.o : test.c chaine_cle.h
	gcc -c test.c

chaine_cle.o : chaine_cle.c chaine_cle.h ../Partie_2/gestion_clef.h
	gcc -c chaine_cle.c



#Fichiers de la partie 2 nécessaires

gestion_clef.o : ../Partie_2/gestion_clef.c ../Partie_1/tests_primalite.h
	gcc  -c ../Partie_2/gestion_clef.c 


signature.o : ../Partie_2/signature.c ../Partie_1/gestion_cryptage.h ../Partie_2/gestion_clef.h
	gcc  -c ../Partie_2/signature.c  




#Fichiers de la partie 1 nécessaires
gestion_cryptage.o : ../Partie_1/gestion_cryptage.c ../Partie_1/gestion_cryptage.h ../Partie_1/tests_primalite.h
	gcc -c ../Partie_1/gestion_cryptage.c

tests_primalite.o : ../Partie_1/tests_primalite.c ../Partie_1/tests_primalite.h
	gcc -c ../Partie_1/tests_primalite.c 
