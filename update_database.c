#include "insearch.h"

// Update the in-memory database using a backup file
int update_database(c_db *hash_t, f_list **head)
{
    char newfile[100];             // Buffer for backup file name
    char backup_word_file[30];     // Buffer for file name from backup
    int index;                     // Hash index

    // Ask user for backup file name
    printf("[INPUT] Enter backup file name to update database : ");
    scanf("%s", newfile);

    // Open backup file in read mode
    FILE *fptr = fopen(newfile, "r");
    if (fptr == NULL)
    {
        printf("[ERROR] Backup file not found : %s\n", newfile);
        return FAILURE;
    }

    // Read each record from backup file
    while (fscanf(fptr, "%s", newfile) != EOF)
    {
        // Validate record format
        if (newfile[0] != '#')
        {
            printf("[ERROR] Invalid backup file format detected.\n");
            fclose(fptr);
            return FAILURE;
        }

        // Extract hash index
        index = atoi(strtok(&newfile[1], ";"));

        // Allocate main node
        m_node *m_new = malloc(sizeof(m_node));
        if (m_new == NULL)
            return FAILURE;

        m_new->main_link = NULL;
        m_new->sub_link = NULL;

        // Extract word and file count
        strcpy(m_new->word, strtok(NULL, ";"));
        m_new->file_count = atoi(strtok(NULL, ";"));

        s_node *stemp = NULL; // Tail pointer for sub nodes

        // Create sub nodes for each file
        for (int i = 0; i < m_new->file_count; i++)
        {
            s_node *s_inner = malloc(sizeof(s_node));
            if (s_inner == NULL)
                return FAILURE;

            // Extract file name and word count
            strcpy(backup_word_file, strtok(NULL, ";"));
            strcpy(s_inner->file_name, backup_word_file);
            s_inner->word_count = atoi(strtok(NULL, ";"));
            s_inner->s_sub_link = NULL;

            // Remove duplicate files from file list
            f_list *curr = *head;
            f_list *prev = NULL;

            while (curr != NULL)
            {
                if (strcmp(curr->f_name, backup_word_file) == 0)
                {
                    if (prev == NULL)
                        *head = curr->link;
                    else
                        prev->link = curr->link;

                    f_list *to_free = curr;
                    curr = curr->link;
                    free(to_free);
                }
                else
                {
                    prev = curr;
                    curr = curr->link;
                }
            }

            // Attach sub node to main node
            if (m_new->sub_link == NULL)
                m_new->sub_link = s_inner;
            else
                stemp->s_sub_link = s_inner;

            stemp = s_inner;
        }

        // Insert main node into hash table
        if (hash_t[index].m_link == NULL)
        {
            hash_t[index].m_link = m_new;
        }
        else
        {
            m_node *temp = hash_t[index].m_link;
            while (temp->main_link != NULL)
                temp = temp->main_link;
            temp->main_link = m_new;
        }
    }

    fclose(fptr);
    printf("[SUCCESS] Database updated successfully from backup.\n");
    return SUCCESS;
}
