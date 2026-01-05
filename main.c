#include "inverted_search.h"

int main(int argc, char *argv[])
{
    Flist *fhead = NULL;
    Mlist *htable[SIZE] = {NULL};

    if (argc < 2)
    {
        printf("INFO : No input files provided\n");
        return 0;
    }

    /* load backup first */
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "backup.txt") == 0)
        {
            load_database("backup.txt", htable, &fhead);
        }
    }

    /* insert remaining files (staged only) */
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "backup.txt") != 0)
        {
            insert_file(&fhead, argv[i]);
        }
    }

    int choice;
    char word[50];

    while (1)
    {
        printf("\n1. Create database\n");
        printf("2. Search data\n");
        printf("3. Update database\n");
        printf("4. Display database\n");
        printf("5. Save database\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            create_database(fhead, htable);
            break;
        case 2:
            printf("Enter word: ");
            scanf("%s", word);
            search_database(htable, word);
            break;
        case 3:
            update_database(htable, fhead);
            break;
        case 4:
            display_database(htable);
            break;
        case 5:
            save_database(htable, "backup.txt");
            break;
        case 6:
            printf("INFO : Exiting program\n");
            exit(0);
        default:
            printf("INFO : Invalid choice\n");
        }
    }
}
