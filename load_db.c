#include "inverted_search.h"

int load_database(char *fname, Mlist *htable[], Flist **fhead)
{
    FILE *fp = fopen(fname, "r");
    if (!fp)
    {
        printf("INFO : Unable to open backup file\n");
        return FAILURE;
    }

    printf("INFO : Loading database from backup file\n");

    char line[256];

    while (fgets(line, sizeof(line), fp))
    {
        int index, file_count, word_count;
        char word[50], file_name[50];

        char *token = strtok(line, "#;");
        index = atoi(token);

        token = strtok(NULL, ";");
        strcpy(word, token);

        token = strtok(NULL, ";");
        file_count = atoi(token);

        Mlist *newm = malloc(sizeof(Mlist));
        strcpy(newm->word, word);
        newm->file_count = file_count;
        newm->slink = NULL;
        newm->next = htable[index];
        htable[index] = newm;

        for (int i = 0; i < file_count; i++)
        {
            token = strtok(NULL, ";");
            strcpy(file_name, token);

            token = strtok(NULL, ";");
            word_count = atoi(token);

            Slist *news = malloc(sizeof(Slist));
            strcpy(news->file_name, file_name);
            news->word_count = word_count;
            news->next = newm->slink;
            newm->slink = news;

            /* mark file as indexed */
            Flist *temp = *fhead;
            int found = 0;
            while (temp)
            {
                if (strcmp(temp->file_name, file_name) == 0)
                {
                    found = 1;
                    temp->indexed = 1;
                    break;
                }
                temp = temp->next;
            }

            if (!found)
            {
                Flist *newf = malloc(sizeof(Flist));
                strcpy(newf->file_name, file_name);
                newf->indexed = 1;
                newf->next = *fhead;
                *fhead = newf;
            }
        }
    }

    fclose(fp);
    printf("INFO : Database loaded successfully\n");
    return SUCCESS;
}
