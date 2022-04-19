all :  main_final test_gestion_vote_blocks test_tree

test_gestion_vote_blocks.o : test_gestion_vote_blocks.c ../Partie_4/block.h gestion_vote_block.h ../Partie_2/gestion_votants_candidats.h ../Partie_2/gestion_clef.h ../Partie_3/chaine_cle.h ../Partie_3/chaine_protected.h 
	gcc -c test_gestion_vote_blocks.c -lssl -lcrypto


test_gestion_vote_blocks : test_gestion_vote_blocks.o ../Partie_4/block.o block_tree.o gestion_vote_block.o gestion_votants_candidats.o gestion_clef.o chaine_cle.o chaine_protected.o signature.o gestion_hachage.o tests_primalite.o gestion_cryptage.o
	gcc -o test_gestion_vote_blocks test_gestion_vote_blocks.o ../Partie_4/block.o block_tree.o gestion_vote_block.o gestion_votants_candidats.o gestion_clef.o chaine_cle.o chaine_protected.o signature.o gestion_hachage.o tests_primalite.o gestion_cryptage.o -lssl -lcrypto



test_tree.o : test_tree.c ../Partie_4/block.h block_tree.h ../Partie_2/gestion_votants_candidats.h ../Partie_2/gestion_clef.h ../Partie_3/chaine_cle.h ../Partie_3/chaine_protected.h 
	gcc -c test_tree.c -lssl -lcrypto

test_tree : test_tree.o  ../Partie_4/block.o block_tree.o gestion_votants_candidats.o gestion_clef.o chaine_cle.o chaine_protected.o signature.o gestion_hachage.o tests_primalite.o gestion_cryptage.o
	gcc -o test_tree test_tree.o  ../Partie_4/block.o block_tree.o gestion_votants_candidats.o gestion_clef.o chaine_cle.o chaine_protected.o signature.o gestion_hachage.o tests_primalite.o gestion_cryptage.o -lssl -lcrypto


main_final.o : main_final.c  ../Partie_4/block.h gestion_vote_block.h ../Partie_2/gestion_votants_candidats.h ../Partie_2/gestion_clef.h ../Partie_3/chaine_cle.h ../Partie_3/chaine_protected.h 
	gcc -c main_final.c -lssl -lcrypto


main_final : main_final.o  ../Partie_4/block.o block_tree.o gestion_vote_block.o gestion_votants_candidats.o gestion_clef.o chaine_cle.o chaine_protected.o signature.o gestion_hachage.o tests_primalite.o gestion_cryptage.o
	gcc -o main_final main_final.o  ../Partie_4/block.o block_tree.o gestion_vote_block.o gestion_votants_candidats.o gestion_clef.o chaine_cle.o chaine_protected.o signature.o gestion_hachage.o tests_primalite.o gestion_cryptage.o -lssl -lcrypto





block_tree.o : block_tree.c block_tree.h ../Partie_4/block.h ../Partie_3/chaine_protected.h ../Partie_2/signature.h ../Partie_2/gestion_clef.h
	gcc -c block_tree.c -lssl -lcrypto

gestion_vote_block.o : gestion_vote_block.c gestion_vote_block.h  block_tree.h ../Partie_4/block.h ../Partie_3/chaine_protected.h ../Partie_2/signature.h ../Partie_2/gestion_clef.h ../Partie_3/gestion_hachage.h
	gcc -c gestion_vote_block.c -lssl -lcrypto




#Fichiers des parties précédentes

	
block.o : ../Partie_4/block.c  ../Partie_4/block.h ../Partie_3/chaine_protected.h ../Partie_2/signature.h ../Partie_2/gestion_clef.h
	gcc -c  ../Partie_4/block.c -lssl -lcrypto


gestion_clef.o : ../Partie_2/gestion_clef.c ../Partie_1/tests_primalite.h 
	gcc  -c ../Partie_2/gestion_clef.c

chaine_protected.o : ../Partie_3/chaine_protected.c ../Partie_3/chaine_protected.h ../Partie_2/signature.h
	gcc -c ../Partie_3/chaine_protected.c


chaine_cle.o : ../Partie_3/chaine_cle.c ../Partie_3/chaine_cle.h ../Partie_2/gestion_clef.h
	gcc -c ../Partie_3/chaine_cle.c

signature.o : ../Partie_2/signature.c ../Partie_1/gestion_cryptage.h ../Partie_2/gestion_clef.h
	gcc  -c ../Partie_2/signature.c 

gestion_cryptage.o : ../Partie_1/gestion_cryptage.c ../Partie_1/gestion_cryptage.h ../Partie_1/tests_primalite.h
	gcc -c ../Partie_1/gestion_cryptage.c


gestion_hachage.o : ../Partie_3/gestion_hachage.c ../Partie_3/chaine_protected.c ../Partie_3/chaine_protected.h ../Partie_2/signature.h ../Partie_2/gestion_clef.h
	gcc -c ../Partie_3/gestion_hachage.c


tests_primalite.o : ../Partie_1/tests_primalite.c ../Partie_1/tests_primalite.h
	gcc -c ../Partie_1/tests_primalite.c 

gestion_votants_candidats.o : ../Partie_2/gestion_votants_candidats.c ../Partie_2/gestion_clef.h ../Partie_2/signature.h
	gcc -c ../Partie_2/gestion_votants_candidats.c

	

clean:
	rm -f *.o main_final test_gestion_vote_blocks test_tree
