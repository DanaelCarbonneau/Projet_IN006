
#include"gestion_hachage.h"


HashCell* create_hashcell(Key* key){
    HashCell* res = (HashCell*) malloc(sizeof(HashCell));
    res->key = key;
    res->val = 0;
}