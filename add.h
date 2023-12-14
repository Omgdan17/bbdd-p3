#ifndef ADD_H
#define ADD_H


#include "types.h"
#include "index.h"

Status add(Index *index, Index *lst, FILE *db, Method method, int book_id, char *isbn, char *title, char *printedBy);

int add_to_file(FILE *db, size_t size, int book_id, char *isbn, char *title, char *printedBy);

#endif