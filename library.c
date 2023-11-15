#include "types.h"

struct _indexbook {
    int key; /*Book isbn*/
    long offset; /*Book is stored in disk at this position*/
    size_t size; /*Book record size. This is a redundant field that helps in the implementation*/
};


/*Estructura para despues de la entrega parcial*/
struct _indexdeletedbook {
    size_t register_size; /*size of the deleted register*/
    size_t offset; /*Recrod's offset in file*/
};

void library_init(FILE f);

void library_init(FILE f) {
    int book_id;
    char isbn[16];
    char title[128];
    char printedBy[128];

    
}



int main(int argc, char argv[]) {
    
    if(argc > 2) {
        return ERROR;
    }

    if(strcmp(argv[1],"add") == 0) {
        add_book(argv[2]);
    }

    else if(strcmp(argv[1],"find") == 0) {
        find_book(argv[2]);
    }

    else {
        printf("Invalid arguments");
    }

    return 0;
}