
#include"gestion_hachage.h"


HashCell* create_hashcell(Key* key){
    HashCell* res = (HashCell*) malloc(sizeof(HashCell));
    if (res == NULL){
		printf("Erreur allocation!");
		return NULL;
	}
    res->key = key;
    res->val = 0;
    return res;
}

int hash_function(Key* key, int size){
	return (key->n + key->val)%size; /*A revoir !!!*/
}

int compare_cles(Key* k1, Key* k2){
	return (k1->val == k2->val) && (k1->n == k2->n);
}

int find_position(HashTable* t, Key* key){ /*A revoir !!!*/
	int pos_init = hash_function(key,t->size);
	int pos = pos_init;
	while ( (pos != pos_init-1) && (t->tab[pos] != NULL)){
		if (compare_cles(t->tab[pos_init],key)){
			return pos;
		}else{
			pos++; /*Gestion par probing linéaire : s'il n'est pas là, essayer le suivant.*/
		}
		if (pos >= t->size){ /*Si on est arrivé au bout de la table, recommencer au début.
		Continuer jusqu'à ce qu'on revienne à pos_init.*/
			pos = 0;
		}
	} if ((pos == pos_init-1) && (t->tab[pos]!=NULL)){
		printf("Table pleine!"); /*D'après la remarque, on ne devrait jamais rencontrer cette situation.*/
		return -1;
	}
	return pos;
}
	     
HashTable* create_hashtable(CellKey* keys, int size){
	HashTable* h_table = (HashTable*)malloc(sizeof(HashTable));
	h_table->size = size;
	h_table->tab = (HashCell**)malloc(size*sizeof(HashCell*));

	/*utile???*/
	for (int i = 0; i < size; i++){
		h_table->tab[i] = NULL;
	}
	
	CellKey* courant = keys;
	int pos;
	while (courant){
		HashCell* cell = create_hashcell(courant->data);
		pos = find_position(courant->data,size);
		/*D'après la remarque on trouve toujours ici une position.*/
		h_table->tab[pos] = cell;
		courant = courant->next;
	}
	return h_table;
}
	      
void delete_hashtable(HashTable* t){
	HashCell* cell_courant;
	for (int i = 0; i < t->size; i++){
		cell_courant = t->tab[i];
		if (cell_courant){
			/*Est-ce qu'on veut free les clés aussi???*/
			free(cell_courant->key);
		}		
		free(cell_courant);
	} free(t->tab);
	free(t);
}

Key* find_winner(HashTable* H_c){
    if(H_c->tab==NULL){
        printf("Erreur, table de hachage vide !");
        return NULL;
    }

    HashCell* gagnant_provisoire = H_c->tab[0];
    
    for(int i = 0 ; i < H_c->size ; i++){
        if( (H_c->tab[i]) && (H_c->tab[i]->val> gagnant_provisoire->val) ){     //Attention, il faut bien vérifier que la case n'est pas nulle !
            gagnant_provisoire = H_c->tab[i];
        }
    }
    return gagnant_provisoire->key;
}


Key* compute_winner(CellProtected* decl, CellKey* candidates, CellKey* voters, int sizeC, int sizeV){

    /*On commence par créer les deux tables de hachage votants et candidats*/
    HashTable* H_c = create_hashtable(candidates,sizeC);                    //Table de hachage des candidats
    HashTable* H_v = create_hashtable(voters,sizeV);                        //Table de hachage de la liste électorale

    /*On parcourt la liste des déclarations pour mettre à jour nos tables de hachages*/

    CellProtected* courant = decl;

    while(courant){

        /*Vérifier que la clé de notre déclaration courante est dans la table de hachage H_v*/
        int pos_hypo_v = find_position(H_v,courant->data->pKey);//Position hypothétique de la clé de notre courant dans la hash table
        
        /*Mise à jour du nombre de votants pour le candidat*/
        if((H_v->tab[pos_hypo_v])&&(H_v->tab[pos_hypo_v]->val==0)){    //On vérifie que notre votant est dans la table et qu'il n'a pas déjà voté

            Key* candidat_choisi = str_to_key(courant->data->mess);     //On récupère le candidat choisi

            /*On vérifie que ce candidat est bien dans notre liste*/
            int pos_hypo_c = find_position(H_c,candidat_choisi);    //Position hypothétique du candidat dans la table

            if(H_c->tab[pos_hypo_c]!=NULL){
                H_c->tab[pos_hypo_c]->val++;            //On ajoute une voix au candidat
                H_v->tab[pos_hypo_v]=1;                 //Le votant dans la tab a alors déjà voté
            }
        }
        courant = courant->next;                //On a fini de traiter le votant courant, on passe au suivant
    }
    /*On peut retourner le gagnat selon notre fonction find_winner*/
    return find_winner(H_c);

}
