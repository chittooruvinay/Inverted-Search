#include "inverted_search.h"

int search_database(Mlist *htable[], char *word)
{
    int index = tolower(word[0]) - 'a';
    if (index < 0 || index >= SIZE)
    {
        printf("INFO : Invalid word\n");
        return FAILURE;
    }

    Mlist *mtemp = htable[index];
    while (mtemp)
    {
        if (strcmp(mtemp->word, word) == 0)
        {
            printf("INFO : Word '%s' found in %d file(s)\n",
                   word, mtemp->file_count);

            Slist *stemp = mtemp->slink;
            while (stemp)
            {
                printf("%s -> %d times\n",
                       stemp->file_name,
                       stemp->word_count);
                stemp = stemp->next;
            }
            return SUCCESS;
        }
        mtemp = mtemp->next;
    }

    printf("INFO : Word '%s' not found\n", word);
    return FAILURE;
}
