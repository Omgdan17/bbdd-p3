#include "loop.h"

void loop(Index *index){
    Command cmd = NO_CMD;
    char input[MAX_LENGTH] = "", *command; 
    char *cmd_to_str[NCMD] = {"exit", "add", "find", "del", "printInd", "printLst", "printRec"};
    int i=0;
    int len;
    char *id, *isbn, *title, *printedBy;

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

        id = strtoi(strtok(NULL, "|"));
        isbn = strtok(NULL, "|");
        title = strtok(NULL, "|");
        printedBy = strtok(NULL, " ");

        switch(cmd){
            case EXIT:
                break;
            case ADD:
                add(index, id, isbn, title, printedBy);
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

int main(int argc, char *argv[]){
    Index *index = NULL;
    if (argc )
    /*función para cargar los datos de un fichero*/

    loop(index);

    /*función para guardar los datos en un fichero*/

    return 0;
}