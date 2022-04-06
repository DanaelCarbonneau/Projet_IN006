#include"block.h"






void write_block(char* nom_fichier, Block* b){
    FILE* fichier_blocks = fopen(nom_fichier,'w');

    if(fichier_blocks==NULL){
        printf("Erreur à l'ouverture du fichier !\n");
        return;
    }

    char* cle = key_to_str(b->author);
    char* hash = b->hash;
    char* previous = b->previous_hash;
    fprintf(fichier_blocks,"%s\t%s \t%s\n",cle,hash,previous);
    CellProtected* courant = b->votes;
    char* prtctd_cour;
    while(courant){
        prtctd_cour = protected_to_str(courant->data);
        fprintf(fichier_blocks,"%s\n",prtctd_cour);
        courant = courant->next;
        free(prtctd_cour);
    }
    fprintf(fichier_blocks,"~");      ///Le tilde permet de savoir qu'on a fini de lire le block
    free(cle);
}

Block* read_block(char*nom_fichier){
    /*On ouvre le fichier*/
    FILE* fichier_lecture = fopen(nom_fichier,'r');

    if(fichier_lecture == NULL){
        printf("Erreur d'ouverture du fichier !\n");
        return NULL;
    }

    /*On alloue le block résultat*/
    Block* res = (Block*) malloc(sizeof(Block));

    if(res==NULL){
        printf("Erreur d'allocation ! \n");
        return NULL;
    }

    /*On déclare les variables de notre block et on les remplit à partir du fichier*/
    char cle[256];
    char* hash;
    char*previous;
    char buffer[256];
    fgets(buffer,256,fichier_lecture);

    if(sscanf(buffer,"%s\t%s\t%s\n",cle,hash,previous)!=3){
        printf("Erreur de formatage dans le fichier (infos avant la chaine) !\n");
        free(res);
        return NULL;
    }

    res->author = key_to_str(cle);
    res->hash = hash;
    res->previous_hash = previous;
    res->votes = NULL;

    /*On va lire lignes par lignes les protected pour les ajouter dans la liste votes*/

    fgets(buffer,256,fichier_lecture);

    Protected* pr;
    while (buffer != "~"){      //On place ce caractère à la fin des protected rentrés dans le fichier

        pr = str_to_protected(buffer);          /*Si on a un fichier qui n'a pas le tilde à la fin, au moment où
                                                La première ligne lue qui ne respecte pas le format d'un protected
                                                nous fera sortir de la boucle, donc pas de problème de terminaison*/
        if (pr == NULL){
            printf("Les lignes suivantes ne seront pas prises en compte");
            return res;
        }
        res->votes = ajoutEnTete_protected(pr,res->votes);          //On ajoute notre protected
        /*Le protected n'est pas libéré ici car il est simplement référencé lorsqu'on créé une cellule.*/

        fgets(buffer,256,fichier_lecture);        //On lit la ligne suivante
    }
    
    fclose(fichier_lecture);
    return res;
}


unsigned char* hash_function_SHA256(const char* s){
    unsigned char* hash = SHA256(s,strlen(s),0);
    return hash;
}

char* block_to_str(Block* B){

}

int verifie_nb_d(unsigned char* hash,int d){

}

void compute_proof_of_work(Block *B, int d){
    B->nonce = 0;

    char* s = block_to_str(B);
    B->hash = hash_function_SHA256(s);

    int verif_d = verifie_nb_d(B->hash,d);

    while (verif_d = 0){
        B->hash = hash_function_SHA256(s);
        B->nonce ++;
        verif_d = verifie_nb_d(B->hash,d);
    }
    
}