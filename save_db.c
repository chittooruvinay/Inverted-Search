#include "inverted_search.h"

int save_database(Mlist *htable[], char *fname)
{
    FILE *fp = fopen(fname, "w");
    if (!fp)
    {
        printf("INFO : Unable to create backup file\n");
        return FAILURE;
    }

    for (int i = 0; i < SIZE; i++)
    {
        Mlist *mtemp = htable[i];
        while (mtemp)
        {
            fprintf(fp, "#%d;%s;%d;",
                    i, mtemp->word, mtemp->file_count);

            Slist *stemp = mtemp->slink;
            while (stemp)
            {
                fprintf(fp, "%s;%d;",
                        stemp->file_name,
                        stemp->word_count);
                stemp = stemp->next;
            }
            fprintf(fp, "#\n");
            mtemp = mtemp->next;
        }
    }

    fclose(fp);
    printf("INFO : Database saved successfully\n");
    return SUCCESS;
}
