#include <string.h>
#include "gestion_cryptage.h"

typedef struct _signature{
	long* contenu;
	int longueur;
}Signature;

Signature* init_signature(long* content, int size){
	Signature* sign = (Signature*)(malloc(sizeof(Signature)));
	sign->contenu = content;
	sign->longueur = size;
	return sign;
}

Signature* sign(char* mess, Key* sKey){
	long* coded = encrypt(mess,sKey->val,sKey->n);
	//checker cohérence des champs de sKey avec partie 1
	return init_signature(coded,strlen(mess));
}

char* signature_to_str(Signature* sgn){
	char* result = malloc (10*sgn->size*sizeof(char));
	result [0]= '#' ;
	int pos = 1;
	char buffer[156];
	for (int i = 0; i < sgn->size; i ++){
		sprintf(buffer,"%lx", sgn->content[i]);
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

typedef struct _protected{
	Key* pKey;
	char* mess;
	Signature* sgn;
}Protected;

Protected* init_protected(Key* pKey, char* mess, Signature* sgn){
	Protected* p = (Protected*)(malloc(sizeof(Protected)));
	p->pKey = pKey;
	p->mess = strdup(mess); //???RevoirLePartieldeCLOL
	p->sgn = sgn;
}

int verify(Protected* pr){
	Signature* sgn = pr->sgn;
	Key* k = pr->pKey;
	char* mess_decrypte = decrypt(sgn->contenu,sgn->longueur,k->val,k->n);
	//CHECKER PAREIL SI COHERENT AVEC STRCUT KEY
	return strcmp(mess_decrypte,pr->mess);
}



