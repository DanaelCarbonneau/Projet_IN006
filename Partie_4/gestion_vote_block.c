

#include"gestion_vote_block.h"

void submit_vote(Protected* p){
	FILE* f = fopen("Pending_votes.txt","a");
	while ( !feof(f) ) {
        	fgetc(f);
	}
	fprintf(f,"%s",protected_to_str(p));
}




void create_block(CellTree* tree, Key* author, int d){
    Block* b = (Block*) malloc(sizeof(Block));
    if(b==NULL){
        printf("Erreur à l'allocation du block\n");
        return;
    }
    CellTree* previous = last_node(tree);       //Il faut bien récupérer le last node au début pour avoir la valeur de previous_hash

    b->previous_hash = previous->block->hash;
    b->author = author;
    b->votes = read_protected("pending_votes.txt");

    remove("pending_votes.txt");        //Le fichier a été lu, on peut le supprimer

    compute_proof_of_work(b,d);         //On génère le hash de b

    write_block("Pending_block.txt",b);
}


void add_block(int d, char* name){
	Block* new_b = read_block("Pending_block.txt");
	if (verify_block(new_b,d)){
		write_block(name,new_b);
		/* DEPLACER LE BLOCK ??? */
	} remove("Pending_block.txt");
}


int estFils(CellTree* noeud, CellTree* pere){
	char* h1 = hash_to_str(noeud->block->previous_hash);
	char* h2 = hash_to_str(pere->block->hash);
	return !(strcmp(h1,h2));
}







CellTree* read_tree(){
	DIR* rep = opendir("./Blockchain/");
	
	/*Cr�ation de T*/
	CellTree** T;
	int size_T = 0;
	if (rep != NULL){
		struct dirent* dir;
		while ((dir = readdir(rep))){
			if (strcmp(dir->name,".")!=0 && strcmp(dir->name,"..")!=0){
				size_T++;
			}
		}
	}

	T = (CellTree**)(malloc(sizeof(CellTree*)*size_T));
	if (T == NULL){
		printf("Erreur d'allocation m�moire !");
		return NULL;
	}
	
	/*Cr�ation et ajout des noeuds � T*/
	CellTree* noeud;
	int n = 0;
	Block* block;
	if (rep != NULL){
		struct dirent* dir;
		while ((dir = readdir(rep))){
			if (strcmp(dir->name,".")!=0 && strcmp(dir->name,"..")!=0){
				block = read_block(dir->name);
				noeud = create_node(block);
				T[n] = noeud;
				n++;
			}
		}
	}
	
	/*Parcourt des noeuds et liens p�re-fils*/
	CellTree* n_cour; 
	CellTree* fils_potentiel;
	for (int i = 0; i < size_T; i++){
		n_cour = T[i];
		for (int j = 0; j < size_T; j++){
			fils_potentiel = T[j];
			if ( estFils(fils_potentiel,n_cour)){
				add_child(n_cour,fils_potentiel);
			}
		}	
	}

	/*Trouver et retourner la racine*/
	for (int k = 0, k < size_T; k++){
		n_cour = T[k];
		if (n_cour->father == NULL){
			return n_cour;
		}
	}


	closedir(rep);
}

CellProtected* extraction_protected(CellTree* ab){
	if (ab == NULL){
		return NULL;
	}	
	CellProtected* res = ab->block->votes;
	CellProtected* liste_pr_cour;
	CellTree* fils_courant = ab->firstChild;
	CellTree* frere_courant;
	while (fils_courant){
		liste_pr_cour = fils_courant->block->votes;
		fusion_liste_protected(liste_pr_cour, res);
	}
	return res;	
}

Key* compute_winner_BT(CellTree* tree, CellKey* candidates, CellKey* voters, int sizeC, int sizeV){
	CellProtected* liste_pr = extraction_protected(tree);
	liste_pr = supprimer_fausses_declarations(liste_pr);
	Key* gagnant = compute_winner(liste_pr, candidates, voters, sizeC, sizeV);
	return gagnant;
}