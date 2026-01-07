#include "insearch.h"

int display_database(c_db *hash_t)
{
    printf("\n+--------------------------------------------------------------------------------+\n");
    printf("|                         INVERTED SEARCH DATABASE                                |\n");
    printf("+-------+---------------+------------+---------------+------------+\n");
    printf("| Index | Word          | File Count | File Name     | Word Count |\n");
    printf("+-------+---------------+------------+---------------+------------+\n");

    for (int key = 0; key < 28; key++)
    {
        if (hash_t[key].m_link != NULL)
        {
            m_node *m_temp = hash_t[key].m_link;

            while (m_temp != NULL)
            {
                s_node *s_temp = m_temp->sub_link;
                int first = 1;

                while (s_temp != NULL)
                {
                    if (first)
                    {
                        printf("| %-5d | %-13s | %-10d | %-13s | %-10d |\n",
                               key,
                               m_temp->word,
                               m_temp->file_count,
                               s_temp->file_name,
                               s_temp->word_count);
                        first = 0;
                    }
                    else
                    {
                        printf("| %-5s | %-13s | %-10s | %-13s | %-10d |\n",
                               "",
                               "",
                               "",
                               s_temp->file_name,
                               s_temp->word_count);
                    }

                    s_temp = s_temp->s_sub_link;
                }

                printf("+-------+---------------+------------+---------------+------------+\n");
                m_temp = m_temp->main_link;
            }
        }
    }

    printf("[SUCCESS] Database displayed successfully.\n");
    return SUCCESS;
}
