#include "loop.h"

void loop(){
    Command cmd = NO_CMD;
    char input[MAX_LENGTH], *command; 
    char *cmd_to_str[NCMD] = {"exit", "add", "find", "del", "printInd", "printLst", "printRec"};
    int i=0;

    while (cmd != EXIT){
        cmd = NO_CMD;
        fprintf(stdout, "entry: ");
        fgets(input, MAX_LENGTH-1, stdin);
        while (cmd == NO_CMD && i < NCMD){
            if (strcmp(input, cmd_to_str[i]) == 0)
                cmd = i;
            i++;
        }
        fprintf(stdout, "%d\n", cmd);

        switch(cmd){
            case EXIT:
                break;
            case ADD:
                /*función que añade una entrada*/
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

int main(){

    /*función para cargar los datos de un fichero*/

    loop();

    /*función para guardar los datos en un fichero*/

    return 0;
}