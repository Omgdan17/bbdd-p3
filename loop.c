#include "loop.h"

void loop(Index *index){
    Command cmd = NO_CMD;
    char input[MAX_LENGTH] = "", *command; 
    char *cmd_to_str[NCMD] = {"exit", "add", "find", "del", "printInd", "printLst", "printRec"};
    int i=0;
    int len;
    int id;
    char *isbn, *title, *printedBy;

    if (!index) printf("ERRR\n");

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
                if (add(index, id, isbn, title, printedBy))
                    printf("Record with BookID=12346 has been added to the database\n");
            case FIND:
                /*función que busca una entrada*/
            case DEL:
                /*función que borra una entrada*/
            case PRINTIND:
                /*función que hace printInd*/
            case PRINTLST:
                /*función que hace printLst*/
            case PRINTREC:
                /*función que hace printRec*/
            default:
                break;
        }
    }
}

Status loop_init(Index *index, FILE *pf){

    index = index_init(indexbook_print, indexbook_cmp, indexbook_getSize);

    if (!index) printf("COOS\n");


    /*cargar datos del fichero*/

    return OK;

}

void loop_end(Index *index, FILE *pf){

    

    /*guadar datos en el fichero*/

    index_destroy(index);
}

int main(int argc, char *argv[]){
    Index *index = NULL;
    FILE *f = NULL;

    
    if (loop_init(index, f) == OK){
        loop(index);
        loop_end(index, f);
    }

    return 0;
}