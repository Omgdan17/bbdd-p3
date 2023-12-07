#include "types.h"
#include "library.h"
#include "book.h"

int add(Index *index, FILE *db, int book_id, char *isbn, char *title, char *printedBy);

int add_to_file(FILE *db, size_t size, int book_id, char *isbn, char *title, char *printedBy);