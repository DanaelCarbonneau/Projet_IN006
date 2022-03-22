#include "chaine_protected.h"

CellProtected* create_cell_protected(Protected* pr){
	CellProtected* nouv = (CellProtected*)malloc(sizeof(CellProtected));
	if (nouv == NULL){
		printf("Erreur à l'allocation.");
	}
	nouv->data = pr;
	nouv->next = NULL;
	return nouv;
}

CellProtected* ajoutEnTete_protected(Protected* pr, CellProtected* liste){
	CellProtected* nouv = create_cell_protected(pr);
	nouv->next = liste;
	liste = nouv;
}


CellProtected* read_protected(){
	File* f = fopen("../Partie_2/declarations.txt","r");
	if (f==NULL){
		printf("Erreur d'ouverture du fichier.");
	}
	CellProtected* liste = NULL;
	char ligne[256];
	char pr_char[128];
	char bin[128];
	while (fgets(ligne, 256,f)!=NULL){
		if (sscanf(ligne, "%s %s %s",bin,bin,pr_char) == 3){
			Protected* nouv = str_to_protected(pr_char);
			liste = ajoutEnTete_protected(nouv,liste);
		}else{
			printf("Erreur de formatage!");
		}
	}
	return liste;
}

void print_list_protected(CellProtected* LCP){
    CellProtected* courant = LCP;
    while (courant){
        printf("%s",protected_to_str(courant->data));
        courant = courant->next;
    }
}



void delete_cell_protected(CellProtected* c){
    free(c->data);		//Pas besoin de plus ! les données à l'intérieur de la clé sont statiques
    free(c);
}


void delete_list_protected(CellProtected* LCP){
    CellProtected* courant = LCP;
    while (courant){
        courant = LCP;
        LCP = LCP->next;
        delete_cell_protected(courant);
    }    
}
