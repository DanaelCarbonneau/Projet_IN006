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
	FILE* f = fopen("../Partie_2/declarations.txt","r");
	if (f==NULL){
		printf("Erreur d'ouverture du fichier.");
	}
	CellProtected* liste = NULL;
	char ligne[256];
	while (fgets(ligne, 256,f)!=NULL){
		Protected* nouv = str_to_protected(ligne);
		liste = ajoutEnTete_protected(nouv,liste);
	}
	fclose(f);
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
    CellProtected* tmp;
    while (courant){
        tmp = courant->next;
        delete_cell_protected(courant);
        courant = tmp;
    }     
}

CellProtected* supprimer_fausses_declarations(CellProtected* LCP){
	CellProtected* courant = LCP;
	CellProtected* prec = NULL;
	CellProtected* res = LCP;
	while (courant){
		while (courant && verify(courant->data)){
			prec = courant;
			courant = courant->next;
		}
		if (courant && (prec == NULL)){
			res = courant->next;
			delete_cell_protected(courant);
			courant = res;
		}
		else if (courant){
			prec->next = courant->next;
			delete_cell_protected(courant);
			courant = prec->next;
		}
	} return res;
}

