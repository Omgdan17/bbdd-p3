#include "print.h"

int printRec(Index *index, FILE *f){
    if (!index || !f)
        return -1;

    return printRec_rec(index->root, f);
}

int printRec_rec(BSTNode )