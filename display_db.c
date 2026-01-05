#include "inverted_search.h"

void display_database(Mlist *htable[])
{
    int empty = 1;

    for (int i = 0; i < SIZE; i++)
    {
        if (htable[i])
        {
            empty = 0;
            break;
        }
    }

    if (empty)
    {
        printf("Database is empty\n");
        return;
    }

    printf("\nIndex  Word        File_Count  File_Name        Word_Count\n");
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < SIZE; i++)
    {
        Mlist *mtemp = htable[i];
        while (mtemp)
        {
            Slist *stemp = mtemp->slink;

            printf("%-6d %-11s %-11d %-15s %d\n",
                   i, mtemp->word, mtemp->file_count,
                   stemp->file_name, stemp->word_count);

            stemp = stemp->next;
            while (stemp)
            {
                printf("%-6s %-11s %-11s %-15s %d\n",
                       "", "", "",
                       stemp->file_name, stemp->word_count);
                stemp = stemp->next;
            }

            printf("----------------------------------------------------------\n");
            mtemp = mtemp->next;
        }
    }
}
