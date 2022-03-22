#include<stdio.h>

#include"chaine_cle.h"


CellKey* create_cell_key(Key* key){
	CellKey* nouv = (CellKey*)malloc(sizeof(CellKey));
	if (nouv == NULL){
		printf("Erreur à l'allocation.");
	}
	nouv->data = key;
	nouv->next = NULL;
	return nouv;
}

CellKey* ajoutEnTete(Key* key, CellKey* liste){
	CellKey* nouv = create_cell_key(key);
	nouv->next = liste;
	liste = nouv;
}

CellKey* read_public_keys(char* nom_fichier){
	FILE* f = fopen(nom_fichier,"r");
	if (f==NULL){
		printf("Erreur d'ouverture du fichier.");
	}
	CellKey* liste = NULL;
	char ligne[256];
	char key_char[128];
	char bin[128];
	while (fgets(ligne, 256,f)!=NULL){
		if (sscanf(ligne, "%s : %s",bin,key_char) == 2){
			Key* nouv = str_to_key(key_char);
			liste = ajoutEnTete(nouv, liste);
		}else{
			printf("Erreur de formatage!");
		}
	}
	return liste;
}


void print_list_keys(CellKey* LCK){
    CellKey* courant = LCK;
    while (courant){
        printf("%s",key_to_str(courant->data));
        courant = courant->next;
    }
}



void delete_cell_key(CellKey* c){
    free(c->data);		//Pas besoin de plus ! les données à l'intérieur de la clé sont statiques
    free(c);
}


void delete_list_keys(CellKey*LCK){
    CellKey* courant = LCK;
    while (courant){
        courant = LCK;
        LCK = LCK->next;
        delete_cell_key(courant);
    }    
}
