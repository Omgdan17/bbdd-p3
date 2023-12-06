#include "types.h"
#include "library.h"
#include "book.h"

int add(Index *index, int book_id, char *isbn, char *title, char *printedBy);

int add_to_file(int size, int book_id, char *isbn, char *title, char *printedBy);