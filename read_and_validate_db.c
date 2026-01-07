#include "insearch.h"

int read_and_validate(int argc, char *argv[], f_list **head)
{
    // Traverse command-line arguments (skip program name)
    for (int i = 1; i < argc; i++)
    {
        // Validate file (existence, extension, non-empty)
        if (open_files(argv[i]) == SUCCESS)
        {
            f_list *temp = *head;
            int duplicate = 0;

            // Check whether file already exists in the list
            while (temp != NULL)
            {
                if (strcmp(temp->f_name, argv[i]) == 0)
                {
                    printf("[WARNING] Duplicate file ignored : %s\n", argv[i]);
                    duplicate = 1;
                    break;
                }
                temp = temp->link;
            }

            // Add file to linked list if not duplicate
            if (!duplicate)
            {
                f_list *new = malloc(sizeof(f_list));
                strcpy(new->f_name, argv[i]);
                new->link = *head;
                *head = new;

                printf("[INFO] File validated and added : %s\n", argv[i]);
            }
        }
        else
        {
            // Invalid file case
            printf("[ERROR] Invalid file (missing / empty / not .txt) : %s\n", argv[i]);
        }
    }

    printf("[SUCCESS] File validation process completed.\n");
    return SUCCESS;
}

int open_files(char *argv)
{
    // Check file extension
    char *ext = strrchr(argv, '.');
    if (ext && strcmp(ext, ".txt") == 0)
    {
        // Open file and check for non-empty content
        FILE *fptr = fopen(argv, "r");
        if (fptr)
        {
            fseek(fptr, 0, SEEK_END);
            if (ftell(fptr) > 0)
            {
                fclose(fptr);
                return SUCCESS;
            }
            fclose(fptr);
        }
    }

    return FAILURE;
}
