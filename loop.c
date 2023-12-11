#include "loop.h"

void loop(Index *index, char *filename){
    Command cmd = NO_CMD;
    FILE *f = NULL;
    char input[MAX_LENGTH] = "", *command; 
    char *cmd_to_str[NCMD] = {"exit", "add", "find", "del", "printInd", "printLst", "printRec"};
    int i=0;
    int len;
    int id;
    char *isbn, *title, *printedBy;
    int *keys = NULL;

    if (index == NULL) return;

    fprintf(stdout, "Type command and argument/s.\n");

    while (cmd != EXIT){
        i = 0;
        cmd = NO_CMD;
        fprintf(stdout, "entry: ");
        fgets(input, MAX_LENGTH-1, stdin);
        len = strlen(input);
        input[len -1] = ' ';

        command = strtok(input, " ");
        while (cmd == NO_CMD && i < NCMD){
            if (strcmp(command, cmd_to_str[i]) == 0)
                cmd = i;
            i++;
        }

        switch(cmd){
            case EXIT:
                break;
            case ADD:
                id = strtol(strtok(NULL, "|"), NULL, 10);
                isbn = strtok(NULL, "|");
                title = strtok(NULL, "|");
                printedBy = strtok(NULL, " ");
                f = fopen(filename, "ab");
                if (add(index, f, id, isbn, title, printedBy))
                    fprintf(stdout, "Record with BookID=%d has been added to the database\n", id);
                fclose(f);
                break;
            case FIND:
                id = strtol(strtok(NULL, " "), NULL, 10);
                f = fopen(filename, "rb");
                if (!find(index, f, id))
                    fprintf(stdout, "Record with bookId=%d does not exist\n", id);
                fclose(f);
                break;
            case DEL:
                /*función que borra una entrada*/
            case PRINTIND:
                index_inOrder(stdout, index);
                break;
            case PRINTLST:
                /*función que hace printLst*/
            case PRINTREC:
                
                keys = (int*)index_inOrder_keys(index, indexbook_getKey);
                i = 0;
                for (i=0; i<index_numberOfNodes(index); i++){
                    f = fopen(filename, "rb");
                    find(index, f, keys[i]);
                    fclose(f);
                }
                
                free(keys);
                
                break;
            default:
                break;
        }
    }

}

Status loop_init(Index **index, char *filename){
    Status st;
    FILE *f = NULL;
    *index = index_init(indexbook_print, indexbook_cmp, indexbook_getSize, indexbook_free);

    if (!index) return ERROR;

    f = fopen(filename, "rb");
    if (!f) return OK;

    st = index_load(*index, f);

    fclose(f);

    return st;

}

void loop_end(Index *index, char *filename){
    FILE *f = NULL;

    f = fopen(filename, "wb");

    index_save(index, f);

    fclose(f);

    index_destroy(index);
}

int main(int argc, char *argv[]){
    Index *index = NULL;
    char db[32], ind[32], lst[32];

    if (argc != 3) return ERROR;

    sprintf(db, "%s.db", argv[2]);
    sprintf(ind, "%s.ind", argv[2]);
    sprintf(lst, "%s.lst", argv[2]);
    
    if (loop_init(&index, ind) == OK){
        loop(index, db);
        loop_end(index, ind);
    }


    return 0;
}