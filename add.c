#include "add.h"
#include "indexbook.h"
#include "indexdeleted.h"

/**
 * add adds a new book to an index and stores it in memory
*/
Status add(Index *index, Index *lst, char *filename, Method method, int book_id, char *isbn, char *title, char *printedBy){
    IndexBook *ib = NULL;
    size_t size = 0;
    long offset = -1;
    int i;

    if (!index || !lst || !filename) return ERROR;

    if (!(ib = indexbook_init()))
    {
        fprintf(stderr, "Error allocating memory for the register\n");
        indexbook_free(ib);
        return ERROR;
    }

    if (!(indexbook_setKey(ib, book_id)))
    {
        fprintf(stderr, "Error saving the register 1\n");
        indexbook_free(ib);
        return ERROR;
    }

    size += sizeof(book_id);
    for (i = 0; isbn[i] != '\0'; i++)
        ;
    size += i;
    for (i = 0; title[i] != '\0'; i++)
        ;
    size += i + 1;
    for (i = 0; printedBy[i] != '\0'; i++)
        ;
    size += i;

    if (!(indexbook_setSize(ib, size)))
    {
        fprintf(stderr, "Error saving the register 2\n");
        indexbook_free(ib);
        return ERROR;
    }

    switch (method)
    {
    case FIRST:
        offset = index_firstfit(lst, size);
        break;
    case BEST:
        offset = index_bestfit(lst, size);
        break;
    case WORST:
        offset = index_worstfit(lst, size);
        break;
    default:
        break;
    }

    if (offset == -1)
        offset = index_size(index) + index_numberOfElements(index) * sizeof(long);

    if (!(indexbook_setOffset(ib, offset)))
    {
        fprintf(stderr, "Error saving the register 3\n");
        indexbook_free(ib);
        return ERROR;
    }

    if (index_contains(index, ib) == TRUE)
    {
        fprintf(stderr, "Record with BookID = %d exists\n", book_id);
        return ERROR;
    }

    if (!(index_insert(index, ib)))
    {
        fprintf(stderr, "Error saving the register 4\n");
        indexbook_free(ib);
        return ERROR;
    }

    return add_to_file(filename, offset, size, book_id, isbn, title, printedBy);
}
/**
 * add_to_file adds a new book's data to a file
*/
int add_to_file(char *filename, long offset, size_t size, int book_id, char *isbn, char *title, char *printedBy){
    int i = 0, count=0;
    FILE *db = NULL;

    if (!filename || size < 0 || book_id < 0 || !isbn || !title || !printedBy) return -1;

    db = fopen(filename, "rb+");
    if (!db) return -1;

    fseek(db, offset, SEEK_SET);
    
    count += fwrite(&size, sizeof(size_t), 1, db);
    count += fwrite(&book_id, sizeof(int), 1, db);
    for (i = 0; i < strlen(isbn); i++)
        count += fwrite(&isbn[i], sizeof(char), 1, db);
    for (i = 0; i < strlen(title); i++)
        count += fwrite(&title[i], sizeof(char), 1, db);
    count += fwrite("|", sizeof(char), 1, db);
    for (i = 0; i < strlen(printedBy); i++)
        count += fwrite(&printedBy[i], sizeof(char), 1, db);

    fclose(db);

    return count;
}