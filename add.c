#include "add.h"
#include "indexbook.h"

int add(Index *index, int book_id, char *isbn, char *title, char *printedBy){
    IndexBook *ib = NULL;
    size_t size = 0;
    long offset;

    if (!index) return ERROR;

    if (!(ib = indexbook_init())){
        fprintf(stderr, "Error allocating memory for the index\n");
        indexbook_free(ib);
        return ERROR;
    }

    if (!(indexbook_setId(ib, book_id))){
        fprintf(stderr, "Error saving the index 1\n");
        indexbook_free(ib);
        return ERROR;
    }

    size += sizeof(book_id);
    size += sizeof(isbn);
    size += sizeof(title);
    size += sizeof(printedBy);

    if (!(indexbook_setSize(ib, size))){
        fprintf(stderr, "Error saving the index 2\n");
        indexbook_free(ib);
        return ERROR;
    }

    offset = index_size(index);

    if (!(indexbook_setOffset(ib, offset))){
        fprintf(stderr, "Error saving the index 3\n");
        indexbook_free(ib);
        return ERROR;
    }

    if (index_contains(index, ib) == TRUE){
        fprintf(stderr, "Record with BookID = %d exists\n", book_id);
        return ERROR;
    }

    if (!(index_insert(index, ib))){
        fprintf(stderr, "Error saving the index 4\n");
        indexbook_free(ib);
        return ERROR;
    }

    return OK;
}