#include "loop.h"

void loop(Index *index, char *filename){
    Command cmd = NO_CMD;
    FILE *f = NULL;
    char input[MAX_LENGTH] = "", *command; 
    char *cmd_to_str[NCMD] = {"exit", "add", "find", "del", "printInd", "printLst", "printRec"};
    int i=0;
    int len;
    int id;
    char *isbn, *title, *printedBy, *aux_string;

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
                while(fscanf(f, "%s", aux_string) == 1) {
                    fprintf(stdout, "%s", aux_string);
                }
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


    
    if (loop_init(&index, f1) == OK){
        loop(index, strcat(argv[2], ".db"));
        loop_end(index, f1);
    }


    return 0;
}