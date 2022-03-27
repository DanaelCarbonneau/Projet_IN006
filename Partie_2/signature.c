
#include"signature.h"

Signature* init_signature(long* content, int size){
	Signature* sign = (Signature*)(malloc(sizeof(Signature)));
	sign->contenu = content;
	sign->longueur = size;
	return sign;
}

Signature* deep_copy_sgn(Signature* sgn){
	Signature* sign = (Signature*) malloc(sizeof(Signature));
	sign->contenu = (long*) malloc(sgn->longueur *sizeof(long));
	for(int i = 0 ; i < sgn->longueur; i++){
		(sign->contenu)[i] = (sgn->contenu)[i];
	}
	sign->longueur = sgn->longueur;
	return sign;
}

Signature* sign(char* mess, Key* sKey){
	long* coded = encrypt(mess,sKey->val,sKey->n);
	return init_signature(coded,strlen(mess));
}

char* signature_to_str(Signature* sgn){
	char* result = (char*) malloc (10*sgn->longueur*sizeof(char));
	result [0]= '#' ;
	int pos = 1;
	char buffer[156];
	for (int i = 0; i < sgn->longueur; i ++){
		sprintf(buffer,"%lx", sgn->contenu[i]);
		for (int j = 0; j < strlen(buffer) ; j ++){
			result [pos] = buffer [j];
			pos = pos +1;
		}
		result[pos] = '#';
		pos = pos +1;
	}
	result[pos] = '\0';
	result = realloc(result,(pos+1)*sizeof(char));
	return result;
}

Signature* str_to_signature(char* str){
	int len = strlen (str) ;
	long * content = (long*)malloc(sizeof(long)*len);
	int num = 0;
	char buffer [256];
	int pos = 0;
	for (int i = 0; i < len; i++){
		if (str[i] != '#'){
			buffer[pos] = str[i];
			pos = pos+1;
		}else{
			if (pos != 0){
				buffer[pos] = '\0';
				sscanf(buffer, "%lx", &(content[num]));
				num = num + 1;
				pos = 0;
			}
		}
	}
	content = realloc(content,num*sizeof(long));
	return init_signature(content,num);
}

Protected* init_protected(Key* pKey, char* mess, Signature* sgn){
	Protected* p = (Protected*)(malloc(sizeof(Protected)));
	p->pKey = (Key*)malloc(sizeof(Key));
	init_key(p->pKey,pKey->val,pKey->n);			//On fait une deepcopy de la clé
	p->mess = strdup(mess); 
	p->sgn = deep_copy_sgn(sgn);

	return p;
}

int verify(Protected* pr){
	Signature* sgn = pr->sgn;
	Key* k = pr->pKey;
	char* mess_decrypte = decrypt(sgn->contenu,sgn->longueur,k->val,k->n);
	int bon = (!strcmp(mess_decrypte,pr->mess));
	free(mess_decrypte);
	return bon;	//strcmp nous renvoie 0, c'est à dire faux, lorsque nos chaines sont identiques
}


char* protected_to_str(Protected* protected){

	/*On récupère les chaines de caractère de la clé et de la signature*/
	char* cle = key_to_str(protected->pKey);
	char* signature = signature_to_str(protected->sgn);

	/*On récupère la taille à allouer et on fait l'allocation (les chaînes, trois espaces et le caractère d'arrêt)*/
	int taille_allocation = strlen(cle)+strlen(protected->mess)+strlen(signature)+3;
	char * res = (char*) malloc(taille_allocation*sizeof(char));

	sprintf(res,"%s %s %s",cle,protected->mess,signature);
	free(cle);
	free(signature);

	return res;
}

Protected* str_to_protected(char* chaine){
	/*On alloue le résultat*/
	Protected* res =(Protected*) malloc(sizeof(Protected));

	char cleS[256];
	char message[256];
	char signature[256];

	/*On récupère les trois chaînes de caractère à l'aide du formatage*/
	if(sscanf(chaine,"%s %s %s",cleS,message,signature)!=3){
		printf("Erreur dans le formatage !\n");
		return NULL;
	}

	/*On initialise et retourne le protected*/
	Signature* sgn = str_to_signature(signature);
	Key* cle = str_to_key(cleS);
	Protected* pr = init_protected(cle,message,sgn);
	liberer_signature(sgn);
	free(cle);
	return pr;
}

void liberer_signature(Signature* sgn){
	free(sgn->contenu);
	free(sgn);
}
void liberer_protected(Protected*pr){
	free(pr->mess);
	free(pr->pKey);
	liberer_signature(pr->sgn);
	free(pr);
}


