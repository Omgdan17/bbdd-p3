#include "book.h"

struct _Book {
    size_t size;
    int id;
    char *isbn;
    char *title;
    char *printedBy;
};

Book *book_init (){
    Book *book = NULL;

    if (!(book = malloc(sizeof(Book)))) return NULL;

    book->size = 0;
    book->id = NO_ID;
    book->isbn = "";
    book->title = "";
    book->printedBy = "";

    return book;
}

void book_free (void *book){
    if (!book) return;

    free(book);
}

size_t *book_getSize (const Book *book){
    if (!book) return NULL;

    return book->size;
}

int book_getId (const Book *book){
    if (!book) return NO_ID;

    return book->id;
}

char *book_getIsbn (const Book *book){
    if (!book) return NULL;

    return book->isbn;
}

char *book_getTitle (const Book *book){
    if (!book) return NULL;

    return book->title;
}

char *book_getPrintedBy (const Book *book){
    if (!book) return NULL;

    return book->printedBy;
}

Status book_setSize (Book *book){
    size_t size = 0;
    if (!book) return ERROR;

    size += sizeof(book->id);
    size += sizeof(book->isbn);
    size += sizeof(book->title);
    size += sizeof(book->printedBy);

    book->size = size;

    return OK;
}

Status book_setId (Book *book, const int id){
    if (!book || id < 0) return ERROR;

    book->id = id;

    return book_setSize(book);
}

Status book_setIsbn (Book *book, const char *isbn){
    if (!book || !isbn) return ERROR;

    strcpy(book->isbn, isbn);

    return book_setSize(book);
}

Status book_setTitle (Book *book, const char *title){
    if (!book || !title) return ERROR;

    strcpy(book->title, title);

    return book_setSize(book);
}

Status book_setPrintedBy (Book *book, const char *printedBy){
    if (!book || !printedBy) return ERROR;

    strcpy(book->printedBy, printedBy);

    return book_setSize(book);
}

/** 
 * @brief Prints in pf the data of a book.
 *
 * @param pf a pointer to a file
 * @param book a pointer to a book
 *
 * @return Returns the number of characters that have been written 
 * successfully. If there have been errors returns -1.
 */
int book_print (FILE *pf, const Book *book);