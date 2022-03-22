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
