#include "inverted_search.h"

int insert_file(Flist **head, char *fname)
{
    if (!strstr(fname, ".txt"))
    {
        printf("INFO : '%s' is not a .txt file\n", fname);
        return FAILURE;
    }

    FILE *fp = fopen(fname, "r");
    if (!fp)
    {
        printf("INFO : Unable to open file '%s'\n", fname);
        return FAILURE;
    }
    fclose(fp);

    Flist *temp = *head;
    while (temp)
    {
        if (strcmp(temp->file_name, fname) == 0)
        {
            printf("INFO : File '%s' already added\n", fname);
            return FAILURE;
        }
        temp = temp->next;
    }

    Flist *new = malloc(sizeof(Flist));
    strcpy(new->file_name, fname);
    new->indexed = 0;          // 🔒 NOT indexed yet
    new->next = *head;
    *head = new;

    printf("Successfully inserting file name -> %s into file linked list\n", fname);
    return SUCCESS;
}
