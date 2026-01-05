#include "inverted_search.h"

int index_new_files(Flist *fhead, Mlist *htable[])
{
    int committed = 0;
    char word[50];

    Flist *temp = fhead;

    while (temp)
    {
        if (temp->indexed == 1)
        {
            temp = temp->next;
            continue;
        }

        FILE *fp = fopen(temp->file_name, "r");
        if (!fp)
        {
            temp = temp->next;
            continue;
        }

        while (fscanf(fp, "%s", word) != EOF)
        {
            int index = tolower(word[0]) - 'a';
            if (index < 0 || index >= SIZE)
                continue;

            Mlist *mtemp = htable[index];
            while (mtemp)
            {
                if (strcmp(mtemp->word, word) == 0)
                    break;
                mtemp = mtemp->next;
            }

            if (!mtemp)
            {
                Mlist *newm = malloc(sizeof(Mlist));
                strcpy(newm->word, word);
                newm->file_count = 1;
                newm->next = htable[index];
                htable[index] = newm;

                Slist *news = malloc(sizeof(Slist));
                strcpy(news->file_name, temp->file_name);
                news->word_count = 1;
                news->next = NULL;
                newm->slink = news;
            }
            else
            {
                Slist *stemp = mtemp->slink;
                while (stemp)
                {
                    if (strcmp(stemp->file_name, temp->file_name) == 0)
                    {
                        stemp->word_count++;
                        break;
                    }
                    stemp = stemp->next;
                }

                if (!stemp)
                {
                    Slist *news = malloc(sizeof(Slist));
                    strcpy(news->file_name, temp->file_name);
                    news->word_count = 1;
                    news->next = mtemp->slink;
                    mtemp->slink = news;
                    mtemp->file_count++;
                }
            }
        }

        fclose(fp);
        temp->indexed = 1;   // 🔒 commit happens here
        committed = 1;
        temp = temp->next;
    }

    return committed;
}

int update_database(Mlist *htable[], Flist *fhead)
{
    printf("INFO : Updating database...\n");

    if (index_new_files(fhead, htable))
    {
        printf("INFO : Database updated successfully\n");
        return SUCCESS;
    }

    printf("INFO : Database is already up to date\n");
    return FAILURE;
}
