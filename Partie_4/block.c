#include"block.h"


void write_block(char* nom_fichier, Block* b){
    FILE* fichier_blocks = fopen(nom_fichier,"w");

    if(fichier_blocks==NULL){
        printf("Erreur à l'ouverture du fichier (write block)!\n");
        return;
    }

    char* cle = key_to_str(b->author);
    unsigned char* hash = b->hash;
    unsigned char* previous = b->previous_hash;
    int nonce = b->nonce;

    fprintf(fichier_blocks,"%s\n",cle);


    char * s_hash = hash_to_str(hash);
    char * s_prev = hash_to_str(previous);

 

    fprintf(fichier_blocks,"%s\n%s\n%d\n",s_hash,s_prev,nonce);

    free(s_hash);
    free(s_prev);

    

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
    fclose(fichier_blocks);
}

Block* read_block(char*nom_fichier){
    /*On ouvre le fichier*/
    FILE* fichier_lecture = fopen(nom_fichier,"r");
    

    if(fichier_lecture == NULL){
        printf("Erreur d'ouverture du fichier (dans read block)!\n");
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
    unsigned char* hash;
    unsigned char* previous;
    int nonce;
    char buffer[256];
    fgets(buffer,256,fichier_lecture);

    

    if(sscanf(buffer,"%s",cle)!=1){
        printf("Erreur de lecture de la clé\n");
        free(res);
        return NULL;
    }

    char l_hash[256];
    char l_prev[256];

    fgets(l_hash,256,fichier_lecture);
    fgets(l_prev,256,fichier_lecture);

    hash = str_to_hash(l_hash);

    
    previous = str_to_hash(l_prev);

    

    if(hash == NULL || previous == NULL){
        printf("Erreur dans la lecture des valeurs de hachage !\n");
        free(res);
        free(previous);
        free(hash);
        return NULL;
    }

    
    fgets(buffer,256,fichier_lecture);
    if(sscanf(buffer,"%d",&nonce)!=1){
        printf("Erreur dans le scan de la preuve de travail \n");
        free(res);
        return NULL;
    }

    res->author = str_to_key(cle);
    res->hash = hash;
    res->previous_hash = previous;

    res->nonce = nonce;

    /*On va lire lignes par lignes les protected pour les ajouter dans la liste votes*/
    fgets(buffer,256,fichier_lecture);
    
    CellProtected* tete = NULL;
    CellProtected* last = NULL;
    Protected* pr;
    while (strcmp(buffer,"~")!=0){      //On place ce caractère à la fin des protected rentrés dans le fichier

        pr = str_to_protected(buffer);  
                                                /*Si on a un fichier qui n'a pas le tilde à la fin, au moment où
                                                La première ligne lue qui ne respecte pas le format d'un protected
                                                nous fera sortir de la boucle, donc pas de problème de terminaison*/
        if (pr == NULL){
            printf("Les lignes suivantes ne seront pas prises en compte\n");
            return res;
        }

        if (tete == NULL){
            tete = create_cell_protected(pr);
            last = tete;
        } else{

            last->next = create_cell_protected(pr);
            last = last->next;
        }

        fgets(buffer,256,fichier_lecture);        //On lit la ligne suivante
        /*Le protected n'est pas libéré ici car il est simplement référencé lorsqu'on créé une cellule.*/

    }
    res->votes = tete;
    
    
    fclose(fichier_lecture);
    return res;
}


char * hash_to_str(unsigned char* hash){
    int taille_chaine = 3*SHA256_DIGEST_LENGTH +1;     //Un espace et deux caractères par unsigned char du tableau hash, et le caractère de fin
    char * res = malloc((taille_chaine)*sizeof(char));
    char buffer[4];
    int j = 0;
    for(int i = 0 ; i < SHA256_DIGEST_LENGTH ; i ++){
        sprintf(buffer,"%02x ",hash[i]);        //3 caratères et le caractère de fin
        res[j]= buffer[0];
        res[j+1] = buffer[1];
        res[j+2] = buffer[2];

        j = j +3;
    }
    res[taille_chaine-1] = '\0';
    return res;
}

unsigned char * str_to_hash(char * st){
    unsigned char * res = (unsigned char *) malloc(SHA256_DIGEST_LENGTH*sizeof(unsigned char));
    char buffer_l[4];
    unsigned int stock;
    int j = 0;
    for(int i = 0 ; i < 3*SHA256_DIGEST_LENGTH ; i = i + 3){
        buffer_l[0] = st[i];
        buffer_l[1] = st[i+1];
        buffer_l[2] = st[i+2];
        buffer_l[3] = '\0';


        if(sscanf(buffer_l,"%02x",&stock)!=1){
            printf("Erreur de formatage du hachage hexadécimal\n");
            free(res);
            return NULL;
        }
        res[j] = stock;
        j++;
    }
    return res;
}

char* block_to_str(Block* B){
    /*On veut d'abord calculer la taille exacte à allouer (couteux mais une seule fois X realloc nombreux ?)*/
    /*On connait la taille des char* immédiatement grace à strlen*/
    char* cle = key_to_str(B->author);
    unsigned char* previous = hash_to_str(B->previous_hash);
    
    int taille_tot = strlen(cle)+strlen(previous);


    
    /*On doit parcourir notre liste de protected pour additionner leur taille en char**/

    CellProtected* courant = B->votes;
    char* pr_char;
    int nb_votes = 0;
    while (courant){
        pr_char = protected_to_str(courant->data);
        taille_tot += strlen(pr_char);
        free(pr_char);
        courant = courant->next;
        nb_votes++;
    }
    
    /*On doit connaitre la taille de nonce en char*/
    char nonce_char[256];
    sprintf(nonce_char,"%d",B->nonce);              //Apparement itoa n'existe pas mais on peut faire un sprintf
    taille_tot += strlen(nonce_char);
    
    /*On rajoute 1 pour le \0, et 2+nb_votes espaces*/
    taille_tot+= (3+nb_votes);
    
    /*On peut enfin allouer la chaine*/
    char* res = (char*)(malloc(sizeof(char)*taille_tot));
   
    /*On la remplit*/
    strcpy(res, cle);
    strcat(res," ");
    strcat(res, previous);
    strcat(res," ");
    courant = B->votes;
    while (courant){
        pr_char = protected_to_str(courant->data);
        strcat(res,pr_char);
        free(pr_char);
        strcat(res," ");
        courant = courant->next;
    }
    strcat(res,nonce_char);
    
    /*On libère ce qui reste de mémoire allouée*/
    free(cle);
    free(previous);
    
    /*On retourne notre chaine*/
    return res;
    
}

unsigned char* hash_function_SHA256(const char* s){
    unsigned char* hash = SHA256(s,strlen(s),0);
    return hash;
}




int verifie_nb_d(unsigned char *hash, int d) {
    for (int i = 0; i < d/2; i++) {
        if (hash[i] != 0) {
            return 0;
        }
    }
    if ( ((d % 2) == 1) &&  ( (hash[(d/2)] & 0b11110000) != 0b00000000)) {      //Si notre d est impair, on doit regarder une case de plus, mais seulement le premier des deux chiffres de la représentation en hexadécimal
        return 0;
    }

    return 1;
}


void compute_proof_of_work(Block *B, int d){
    B->nonce = 0;
    

    int verif_d = 0;
    char* s;
    while(verif_d == 0){
        B->nonce += 1;
        s = block_to_str(B);
        B->hash = hash_function_SHA256(s);

        verif_d = verifie_nb_d(B->hash,d);
        free(s);
    }
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       


int verify_block(Block* B, int d) {
    char* s = block_to_str(B);
    int res = 0;
    char* hash_actuel = hash_to_str(B->hash);
    char* hash_attendu = hash_to_str(hash_function_SHA256(s));
    if (verifie_nb_d(B->hash, d) && (strcmp(hash_attendu,hash_actuel)==0)) {
        res = 1;
    }
    free(hash_attendu);
    free(hash_actuel);
    free(s);
    return res; 
}


void generate_fichier_comparaison(Block* b,int nb_d_max){

    FILE* fichier = fopen("comparaison_d.txt","w");

    if(fichier == NULL){
        printf("Erreur à l'ouverture du fichier\n");
        return;
    }

    /*Variables pour le temps*/
	clock_t temps_initial;
	clock_t temps_final;
	double temps;
    srand(time(NULL));
    
    for (int i = 0; i<nb_d_max; i++){

        temps_initial = clock();
        compute_proof_of_work(b,i);
        temps_final = clock();
        temps = ((double) (temps_final - temps_initial) / (CLOCKS_PER_SEC) );
        fprintf(fichier,"%d\t%.10f\n",i,temps);        
    }
    system("gnuplot commandes.txt");            //On éxécute la commande pour faire le graphique
    fclose(fichier);
}



/*Version respectant les contraintes de l'énoncé
void delete_block(Block* b){
    CellProtected* courant = b->votes;
    CellProtected* tmp;
    while(courant!= NULL){
        tmp = courant->next;
        free(courant);
        courant = tmp;
    }
    free(b);
}
*/

/*Version qui nous semble plus appropriée pour la gestion de la mémoire*/

void delete_block(Block* b){
    delete_cell_protected(b->votes);
    free(b);
}

