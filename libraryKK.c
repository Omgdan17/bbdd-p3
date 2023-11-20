#include "types.h"
#include "library.h"
#include <stdlib.h>

#define INITIAL_SIZE 32

struct _indexbook {
    int key; /*Book isbn*/
    long offset; /*Book is stored in disk at this position*/
    size_t size; /*Book record size. This is a redundant field that helps in the implementation*/
};

struct _registers {
    indexbook *data;
    size_t used;
    size_t size; 
};


/*Estructura para despues de la entrega parcial*/
struct _indexdeletedbook {
    size_t register_size; /*size of the deleted register*/
    size_t offset; /*Recrod's offset in file*/
};

void library_init(FILE f);
int libray_load(char *filename);

void library_init(FILE f) {
    /*int book_id;
    char isbn[16];
    char title[128];
    char printedBy[128];*/

    register *reg = NULL;
    int i;

    
    reg = malloc(sizeof(registers));

    reg->data = malloc(sizeof(indexbook));





    
}



/*int main(int argc, char argv[]) {
    
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
}*/

int main (int argc, char *argv[]){
    FILE *f = NULL;

    if (argc != 1 && argc != 2){
        fprintf(stderr, "Incorrect arguments\n");
        return ERROR;
    }

    library_init();

    if (argc == 2){
        if (libraray_load(argv[2]) == ERROR){
            fprintf(stderr, "Error loading data from %s\n", argv[2]);
            return ERROR;
        }

        fprintf(stdout, "Data from %s loaded\n", argv[2]);
    }



    
    
}