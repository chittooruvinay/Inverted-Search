#include "insearch.h"

int create_database(f_list *head, c_db *arr)
{
    f_list *temp = head;
    char word[30];

    // Traverse through each file in the file list
    while (temp != NULL)
    {
        FILE *fptr = fopen(temp->f_name, "r");
        if (fptr == NULL)
        {
            printf("[ERROR] Unable to open file : %s\n", temp->f_name);
            return FAILURE;
        }

        printf("\n[INFO] Indexing file : %s\n", temp->f_name);
        printf("----------------------------------\n");

        // Read words one by one from the file
        while (fscanf(fptr, "%s", word) != EOF)
        {
            int key = get_hash_index(word[0]);

            // Case 1: No main node exists at this hash index
            if (arr[key].m_link == NULL)
            {
                m_node *m_new = malloc(sizeof(m_node));
                s_node *s_new = malloc(sizeof(s_node));

                if (!m_new || !s_new)
                    return FAILURE;

                // Create first main node
                strcpy(m_new->word, word);
                m_new->file_count = 1;
                m_new->main_link = NULL;
                m_new->sub_link = s_new;

                // Create first sub node
                strcpy(s_new->file_name, temp->f_name);
                s_new->word_count = 1;
                s_new->s_sub_link = NULL;

                arr[key].m_link = m_new;
            }
            else
            {
                // Case 2: Main node already exists – search for the word
                m_node *mtemp = arr[key].m_link;
                m_node *mprev = NULL;
                int word_found = 0;

                while (mtemp != NULL)
                {
                    // Word matched in main node
                    if (strcmp(mtemp->word, word) == 0)
                    {
                        word_found = 1;
                        s_node *stemp = mtemp->sub_link;
                        s_node *sprev = NULL;
                        int file_found = 0;

                        // Search for file in sub nodes
                        while (stemp != NULL)
                        {
                            if (strcmp(stemp->file_name, temp->f_name) == 0)
                            {
                                // Same file found – increment word count
                                stemp->word_count++;
                                file_found = 1;
                                break;
                            }
                            sprev = stemp;
                            stemp = stemp->s_sub_link;
                        }

                        // New file for existing word
                        if (!file_found)
                        {
                            s_node *s_new = malloc(sizeof(s_node));
                            if (!s_new)
                                return FAILURE;

                            strcpy(s_new->file_name, temp->f_name);
                            s_new->word_count = 1;
                            s_new->s_sub_link = NULL;
                            sprev->s_sub_link = s_new;

                            mtemp->file_count++;
                        }
                        break;
                    }
                    mprev = mtemp;
                    mtemp = mtemp->main_link;
                }

                // Case 3: Word not found – create new main node
                if (!word_found)
                {
                    m_node *m_new = malloc(sizeof(m_node));
                    s_node *s_new = malloc(sizeof(s_node));
                    if (!m_new || !s_new)
                        return FAILURE;

                    strcpy(m_new->word, word);
                    m_new->file_count = 1;
                    m_new->main_link = NULL;
                    m_new->sub_link = s_new;

                    strcpy(s_new->file_name, temp->f_name);
                    s_new->word_count = 1;
                    s_new->s_sub_link = NULL;

                    mprev->main_link = m_new;
                }
            }
        }

        printf("[SUCCESS] File indexed successfully : %s\n", temp->f_name);
        fclose(fptr);
        temp = temp->link;
    }

    printf("\n[SUCCESS] Database creation completed.\n");
    return SUCCESS;
}
