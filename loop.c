#include "types.h"
#include "index.h"
#include "add.h"
#include "find.h"
#include "delete.h"

void loop(Index *index, Index *lst, Method method, char *filename)
{
    Command cmd = NO_CMD;
    FILE *f = NULL;
    char input[MAX_LENGTH] = "", *command;
    char *cmd_to_str[NCMD] = {"exit", "add", "find", "del", "printInd", "printLst", "printRec"};
    int i = 0;
    int len;
    int id;
    char *isbn, *title, *printedBy;
    int *keys = NULL;

    if (index == NULL)
        return;

    fprintf(stdout, "Type command and argument/s.\n");

    while (cmd != EXIT)
    {
        i = 0;
        cmd = NO_CMD;
        fprintf(stdout, "entry: ");
        fgets(input, MAX_LENGTH - 1, stdin);
        len = strlen(input);
        input[len - 1] = ' ';

        command = strtok(input, " ");
        while (cmd == NO_CMD && i < NCMD)
        {
            if (strcmp(command, cmd_to_str[i]) == 0)
                cmd = i;
            i++;
        }

        switch (cmd)
        {
        case EXIT:
            break;
        case ADD:
            id = strtol(strtok(NULL, "|"), NULL, 10);
            isbn = strtok(NULL, "|");
            title = strtok(NULL, "|");
            printedBy = strtok(NULL, " ");
            f = fopen(filename, "ab");
            fclose(f);
            if (add(index, lst, filename, method, id, isbn, title, printedBy))
                fprintf(stdout, "Record with BookID=%d has been added to the database\n", id);
            break;
        case FIND:
            id = strtol(strtok(NULL, " "), NULL, 10);
            if (!find(index, filename, id))
                fprintf(stdout, "Record with BookID=%d does not exist\n", id);
            break;
        case DEL:
            id = strtol(strtok(NULL, " "), NULL, 10);
            if (delete (index, lst, id) == OK)
                fprintf(stdout, "Record with BookID=%d has been deleted\n", id);
            else
                fprintf(stdout, "Record with BookID=%d does not exist\n", id);
            break;
        case PRINTIND:
            if (index_print(index, stdout) == 0)
                fprintf(stdout, "The index is empty\n");
            break;
        case PRINTLST:
            if (index_print(lst, stdout) == 0)
                fprintf(stdout, "The index is empty\n");
            break;
        case PRINTREC:
            keys = (int *)index_keys(index, indexbook_getKey);
            if (!keys){
                fprintf(stdout, "The index is empty\n");
                break;
            }
            for (i = 0; i < index_numberOfElements(index); i++)
            {
                find(index, filename, keys[i]);
            }

            free(keys);
            break;
        default:
            fprintf(stdout, "Command %s does not exists\n", command);
            break;
        }
    }
}

Status loop_init(Index **index, Index **lst, char *filename1, char *filename2)
{
    Status st;
    FILE *f = NULL;


    if (!filename1 || !filename2)
        return ERROR;

    *index = index_init(indexbook_print, indexbook_cmp, indexbook_getSize, indexbook_free, indexbook_save);
    *lst = index_init(indexdeleted_print, indexdeleted_cmp, NULL, indexdeleted_free, indexdeleted_save);
    if (!index || !lst)
    {
        index_destroy(*index);
        index_destroy(*lst);
        return ERROR;
    }

    f = fopen(filename1, "rb");
    if (!f)
        return OK;

    st = index_load(*index, f, IBOOK);

    fclose(f);

    f = fopen(filename2, "rb");
    if (!f)
        return OK;

    st = index_load(*lst, f, IDEL);

    fclose(f);

    return st;
}

void loop_end(Index *index, Index *index_lst, char *ind, char *lst)
{
    FILE *f = NULL;

    f = fopen(ind, "wb");

    index_save(index, f);

    fclose(f);

    f = fopen(lst, "wb");

    index_save(index_lst, f);

    fclose(f);

    index_destroy(index);
    index_destroy(index_lst);
}

int main(int argc, char *argv[])
{
    Index *index = NULL, *index_lst = NULL;
    Method method = DEFAULT;
    char db[32], ind[32], lst[32];
    char *method_to_str[NMTH] = {"firstfit", "bestfit", "worstfit"};
    int i = 0;

    if (argc != 3)
        return ERROR;

    while (method == DEFAULT && i < NCMD)
    {
        if (strcmp(argv[1], method_to_str[i]) == 0)
            method = i;
        i++;
    }

    if (method == DEFAULT){
        fprintf(stdout, "Please, enter a valid sequence of arguments: ./library <mathod> <filename>\n");
        fprintf(stdout, "<method> field value must be 'firstfit', 'bestfit' or 'worstfit'\n");
        return ERROR;
    }

    sprintf(db, "%s.db", argv[2]);
    sprintf(ind, "%s.ind", argv[2]);
    sprintf(lst, "%s.lst", argv[2]);

    if (loop_init(&index, &index_lst, ind, lst) == OK)
    {
        loop(index, index_lst, method, db);
        loop_end(index, index_lst, ind, lst);
    }

    return 0;
}