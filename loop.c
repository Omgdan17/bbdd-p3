#include "loop.h"

void loop(Index *index, FILE *db){
    Command cmd = NO_CMD;
    char input[MAX_LENGTH] = "", *command; 
    char *cmd_to_str[NCMD] = {"exit", "add", "find", "del", "printInd", "printLst", "printRec"};
    int i=0;
    int len;
    int id;
    char *isbn, *title, *printedBy;

    if (index == NULL) printf("ERR");

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
                if (add(index, db, id, isbn, title, printedBy))
                    printf("Record with BookID=%d has been added to the database\n", id);
                break;
            case FIND:
                /*función que busca una entrada*/
            case DEL:
                /*función que borra una entrada*/
            case PRINTIND:
                index_inOrder(stdout, index);
                break;
            case PRINTLST:
                /*función que hace printLst*/
            case PRINTREC:
                /*función que hace printRec*/
            default:
                break;
        }
    }
}

Status loop_init(Index **index, FILE *pf){
    *index = index_init(indexbook_print, indexbook_cmp, indexbook_getSize, indexbook_free);

    if (!index) return ERROR;

    /*cargar datos del fichero*/

    return OK;

}

void loop_end(Index *index, FILE *pf){

    

    /*guadar datos en el fichero*/

    index_destroy(index);
}

int main(int argc, char *argv[]){
    Index *index = NULL;
    FILE *f1 = NULL, *f2 = NULL;
    if (argc != 3) return ERROR;

    f2 = fopen(strcat(argv[2], ".db"), "wb");

    
    if (loop_init(&index, f1) == OK){
        loop(index, f2);
        loop_end(index, f1);
    }

    fclose(f2);

    return 0;
}