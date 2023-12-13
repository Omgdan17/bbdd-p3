#include "add.h"
#include "indexbook.h"
#include "indexdeleted.h"

Status add(Index *index, FILE *db, int book_id, char *isbn, char *title, char *printedBy){
    IndexBook *ib = NULL;
    size_t size = 0;
    long offset;
    int i;

    if (!index || !db) return ERROR;

    if (!(ib = indexbook_init())){
        fprintf(stderr, "Error allocating memory for the index\n");
        indexbook_free(ib);
        return ERROR;
    }

    if (!(indexbook_setKey(ib, book_id))){
        fprintf(stderr, "Error saving the index 1\n");
        indexbook_free(ib);
        return ERROR;
    }

    size += sizeof(book_id);
    for (i=0; isbn[i] != '\0'; i++);
    size += i;
    for (i=0; title[i] != '\0'; i++);
    size += i + 1;
    for (i=0; printedBy[i] != '\0'; i++);
    size += i;


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

    return add_to_file(db, size, book_id, isbn, title, printedBy);
}

int add_to_file(FILE *db, size_t size, int book_id, char *isbn, char *title, char *printedBy){
    int i = 0, count=0;

    if (!db || size < 0 || book_id < 0 || !isbn || !title || !printedBy) return -1;

    count += fwrite(&size, sizeof(size_t), 1, db);
    count += fwrite(&book_id, sizeof(int), 1, db);
    for (i=0; i<strlen(isbn); i++)
        count += fwrite(&isbn[i], sizeof(char), 1, db);
    for (i=0; i<strlen(title); i++)
        count += fwrite(&title[i], sizeof(char), 1, db);
    count += fwrite("|", sizeof(char), 1, db);
    for (i=0; i<strlen(printedBy); i++)
        count += fwrite(&printedBy[i], sizeof(char), 1, db);

    return count;
}