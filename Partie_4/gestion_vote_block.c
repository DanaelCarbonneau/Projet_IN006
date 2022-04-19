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
		b->previous_hash = (unsigned char *) malloc(SHA256_DIGEST_LENGTH*sizeof(unsigned char));
		for(int i = 0 ; i < SHA256_DIGEST_LENGTH ; i++){
			b->previous_hash[i] = '0';
		}
	}
	else{
    	CellTree* previous = last_node(tree);       //Il faut bien récupérer le last node au début pour avoir la valeur de previous_hash
		b->previous_hash = previous->block->hash;
		
	}
	
    b->author = author;
	
    b->votes = read_protected("Pending_votes.txt");

    remove("Pending_votes.txt");        //Le fichier a été lu, on peut le supprimer

    compute_proof_of_work(b,d);         //On génère le hash de b
    write_block("Pending_block.txt",b);
}


void add_block(int d, char* name){
	Block* new_b = read_block("Pending_block.txt");
	//compute_proof_of_work(new_b,d);
	
	char buffer[256];
	if (verify_block(new_b,d)){

		sprintf(buffer,"../Blockchain/%s",name);
		write_block(buffer,new_b);
		
	} 
	remove("Pending_block.txt");
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

	
	/*Création et ajout des noeuds � T*/
	rewinddir(rep);

	CellTree* noeud;
	int n = 0;
	Block* block;
	char* nom_f_block;
	if (rep != NULL){
		
		while (dir = readdir(rep)){
			if (strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){
				
				char nom_f_block[271];		//taille de dir->d_name + 14 caractères pour le répertoire + 1 pour l'arrêt

				sprintf(nom_f_block,"../Blockchain/%s",dir->d_name);

				/*Trop coûteux de faire ça dynamiquement ?
				nom_f_block = (char*)(malloc(sizeof(char)*(strlen("../Blockchain/")+strlen(dir->d_name)+1)));
				strcpy(nom_f_block,"../Blockchain/");
				strcat(nom_f_block,dir->d_name);
				*/
			
				block = read_block(nom_f_block);
				
				noeud = create_node(block);
				T[n] = noeud;

				n++;
			}

		}
	}

	/*Parcourt des noeuds et liens p�re-fils*/
	rewinddir(rep);

	CellTree* n_cour; 
	CellTree* fils_potentiel;

	int a_un_pere;
	int racine_trouvee = 0;
	CellTree* frere_orphelin;
	CellTree * racine;

	for (int i = 0; i < size_T; i++){
		n_cour = T[i];
		a_un_pere = 0;
		for (int j = 0; j < size_T; j++){
			fils_potentiel = T[j];
			if ( estFils(fils_potentiel,n_cour)){
				add_child(n_cour,fils_potentiel);
				a_un_pere = 1;
			}
		}
		if (a_un_pere==0){
			if(!racine_trouvee){
				frere_orphelin = T[i];
				racine = T[i];
				racine_trouvee = 1; 
				
			}
			else{
				frere_orphelin->nextBro = T[i];
			}
		}
		
	}

	

	/*On trouve la racine*/
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

	CellTree* prochain_fils = highest_child(ab);
	
	while (prochain_fils){
		liste_pr_cour = prochain_fils->block->votes;
		res = fusion_liste_protected(liste_pr_cour, res);
		prochain_fils = highest_child(prochain_fils);
	}
	return res;		
}

Key* compute_winner_BT(CellTree* tree, CellKey* candidates, CellKey* voters, int sizeC, int sizeV){
	CellProtected* liste_pr = extraction_protected(tree);
	liste_pr = supprimer_fausses_declarations(liste_pr);
	Key* gagnant = compute_winner(liste_pr, candidates, voters, sizeC, sizeV);
	return gagnant;
}
