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
	File* f = fopen(nom_fichier,"r");
	if (f==NULL){
		printf("Erreur d'ouverture du fichier.");
	}
	CellKey* liste = NULL;
	char ligne[256];
	char key_char[128];
	char bin[128];
	while (fgets(ligne, 256,f)!=NULL){
		if (sscanf(ligne, "%s : %s, %s",bin,key_char,bin) == 3){
			CellKey* nouv = create_cell_key(str_to_key(key_char));
			liste = ajoutEnTete(nouv);
		}else{
			printf("Erreur de formatage!");
		}
	}
	return liste;
}
