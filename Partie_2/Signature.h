#ifndef SIGNATUREH
#define SIGNATUREH

#include <string.h>
#include<stdlib.h>
#include<stdio.h>
#include "gestion_cryptage.h"
#include "gestion_clef.h"

typedef struct _signature{
	long* contenu;
	int longueur;
}Signature;

Signature* init_signature(long* content, int size);

Signature* sign(char* mess, Key* sKey);

char* signature_to_str(Signature* sgn);

Signature* str_to_signature(char* str);

typedef struct _protected{
	Key* pKey;
	char* mess;
	Signature* sgn;
}Protected;

Protected* init_protected(Key* pKey, char* mess, Signature* sgn);

int verify(Protected* pr);


#endif