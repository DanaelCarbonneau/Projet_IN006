#include"gestion_vote_block.h"

void submit_vote(Protected* p){
	FILE* f = fopen("Pending_votes.txt","a");
	
	char* pr = protected_to_str(p);
	fprintf(f,"%s\n",pr);
	free(pr);
	fclose(f);
}




void create_block(CellTree* tree, Key* author, int d){
    Block* b = (Block*) malloc(sizeof(Block));
    if(b==NULL){
        printf("Erreur à l'allocation du block\n");
        return;
    }

	if(tree == NULL){
		b->previous_hash = "0";
	}
	else{
    	CellTree* previous = last_node(tree);       //Il faut bien récupérer le last node au début pour avoir la valeur de previous_hash
		b->previous_hash = previous->block->hash;
	}
	
    b->author = author;
    b->votes = read_protected("pending_votes.txt");

    remove("pending_votes.txt");        //Le fichier a été lu, on peut le supprimer

    compute_proof_of_work(b,d);         //On génère le hash de b

    write_block("Pending_block.txt",b);
}


void add_block(int d, char* name){
	Block* new_b = read_block("Pending_block.txt");
	compute_proof_of_work(new_b,d);
	
	char buffer[256];
	printf("%s,%s\n",key_to_str(new_b->author), hash_to_str(new_b->hash));
	//print_list_protected(new_b->votes);

	if (verify_block(new_b,d)){
		printf("Passage\n");
		sprintf(buffer,"../Blockchain/%s",name);
		write_block(buffer,new_b);
		/* DEPLACER LE BLOCK ??? */
	} remove("Pending_block.txt");
}


int estFils(CellTree* noeud, CellTree* pere){
	char* h1 = hash_to_str(noeud->block->previous_hash);
	char* h2 = hash_to_str(pere->block->hash);
	return !(strcmp(h1,h2));
}


CellTree* read_tree(){
	DIR* rep = opendir("../Blockchain/");
	struct dirent* dir;
	
	if(rep == NULL){
		printf("Erreur ouverture du dossier\n");
		return NULL;
	}
	printf("Ouverture du répertoire OK\n");
	
	/*Création de T*/
	CellTree** T;
	int size_T = 0;
	if (rep != NULL){
		while ((dir = readdir(rep))){
			if (strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){
				size_T++;
			}
		}
	} 
	

	T = (CellTree**)(malloc(sizeof(CellTree*)*size_T));
	if (T == NULL){
		printf("Erreur d'allocation mémoire !\n");
		return NULL;
	}

	printf("Creation de T OK\n");
	
	/*Création et ajout des noeuds � T*/
	rewinddir(rep);

	printf("Début de l'ajout des nœuds\n");
	CellTree* noeud;
	int n = 0;
	Block* block;
	char* nom_f_block;
	if (rep != NULL){
		printf("Parcourt du répertoire\n");
		while (dir = readdir(rep)){
			//printf("dir pas null %d", dir == NULL);
			if (strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){
				printf("On lit le block\n");
				
				nom_f_block = (char*)(malloc(sizeof(char)*(strlen("../Blockchain/")+strlen(dir->d_name)+1)));
				strcpy(nom_f_block,"../Blockchain/");
				strcat(nom_f_block,dir->d_name);
			
				block = read_block(nom_f_block);
				free(nom_f_block);

				noeud = create_node(block);
				T[n] = noeud;

				n++;
			}

		}
	}
	printf("Fin du parcourt du répertoire\n");

	/*Parcourt des noeuds et liens p�re-fils*/
	rewinddir(rep);

	CellTree* n_cour; 
	CellTree* fils_potentiel;
	printf("Parcourt du tableau pour faire les liens père fils\n");
	for (int i = 0; i < size_T; i++){
		n_cour = T[i];
		printf("papa est null %d",n_cour->father == NULL);
		for (int j = 0; j < size_T; j++){
			fils_potentiel = T[j];
			printf("On cherche si la case est un fils potentiel\n");
			if ( estFils(fils_potentiel,n_cour)){
				printf("On a trouvé un fils\n");
				add_child(n_cour,fils_potentiel);
				printf("On a fini d'ajouter l'enfant\n");
			}
		}	
		
	}

	/*Trouver et retourner la racine*/
	for (int k = 0; k < size_T; k++){
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