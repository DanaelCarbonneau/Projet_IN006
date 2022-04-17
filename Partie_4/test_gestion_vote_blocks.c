#include <stdio.h>
#include <stdlib.h>
#include<openssl/sha.h>



/* IDENFITIFICATION ACTUELLE DU PROBLÈME : DANS ADD CHILD LE PÈRE NE BOUCLE PAS*/
#include "block.h"
#include "gestion_vote_block.h"


#include "../Partie_2/gestion_votants_candidats.h"
#include "../Partie_2/gestion_clef.h"
#include "../Partie_3/chaine_cle.h"
#include "../Partie_3/chaine_protected.h"

#define D 2
#define VOTANTS 5
#define CANDIDATS 2


int main(){
	generate_random_data(VOTANTS, CANDIDATS);
    CellProtected* liste_decl = read_protected("declarations.txt");
    CellKey* liste_cles_c = read_public_keys("candidates.txt");
    CellKey* liste_cles_v = read_public_keys("keys.txt");

    CellProtected* cour = liste_decl;
    while (cour){
    	char* tmp = protected_to_str(cour->data);
    	printf("%s\n",tmp);
    	free(tmp);
    	submit_vote(cour->data);
    	cour = cour->next;
    }

    Key* k_auteur_public = (Key*) malloc(sizeof(Key));
    Key* k_auteur_prive = (Key*) malloc(sizeof(Key));
    init_pair_keys(k_auteur_public,k_auteur_prive,3,7);

    create_block(NULL, k_auteur_public, 2);
    add_block(2,"mon_joli_block");
    
    CellTree* mon_arbre = read_tree();

    print_tree(mon_arbre);


}
