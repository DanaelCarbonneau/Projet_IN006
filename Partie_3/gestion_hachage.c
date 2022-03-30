
#include"gestion_hachage.h"


HashCell* create_hashcell(Key* key){
    HashCell* res = (HashCell*) malloc(sizeof(HashCell));
    if (nouv == NULL){
		printf("Erreur allocation!");
		return NULL;
	}
    res->key = key;
    res->val = 0;
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
	} if ((pos == pos_init-1) && (t->tab[pos]!=NULL){
		printf("Table pleine!"); /*Ou alors on gère par chainage une fois que table toute pleine?*/
		return -1;
	}
	return pos;
}

