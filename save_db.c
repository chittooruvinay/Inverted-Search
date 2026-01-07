#include "insearch.h"

int save_database(c_db *hash_t)
{
    char database[15];

    // Ask user for backup file name
    printf("[INPUT] Enter database file name (eg: backup.txt) : ");
    scanf("%s", database);

    // Open database file in write mode
    FILE *fp = fopen(database, "w");
    if (fp == NULL)
    {
        printf("[ERROR] Unable to create or open file : %s\n", database);
        return FAILURE;
    }

    // Traverse hash table buckets
    for (int key = 0; key < 28; key++)
    {
        // Process only non-empty buckets
        if (hash_t[key].m_link != NULL)
        {
            m_node *m_temp = hash_t[key].m_link;

            // Traverse main nodes
            while (m_temp != NULL)
            {
                // Write main node data -> #index;word;file_count;
                fprintf(fp, "#%d;%s;%d;",
                        key, m_temp->word, m_temp->file_count);

                s_node *s_temp = m_temp->sub_link;

                // Write sub node data -> file_name;word_count;
                while (s_temp != NULL)
                {
                    fprintf(fp, "%s;%d;",
                            s_temp->file_name, s_temp->word_count);
                    s_temp = s_temp->s_sub_link;
                }

                // End of one word record
                fprintf(fp, "#\n");
                m_temp = m_temp->main_link;
            }
        }
    }

    fclose(fp);
    printf("[SUCCESS] Database saved successfully to '%s'.\n", database);

    return SUCCESS;
}
