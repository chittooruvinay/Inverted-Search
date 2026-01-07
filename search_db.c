#include "insearch.h"

int search_database(c_db *hash_table, char *word)
{
    // Get hash index based on first character of word
    int index = get_hash_index(word[0]);

    // Access main node list at computed index
    m_node *m_temp = hash_table[index].m_link;

    // Traverse main nodes to find the word
    while (m_temp != NULL)
    {
        if (strcmp(m_temp->word, word) == 0)
        {
            // Word found in database
            printf("[SUCCESS] Word '%s' found in %d file(s)\n",
                   word, m_temp->file_count);

            s_node *s_temp = m_temp->sub_link;

            // Display file-wise word count
            while (s_temp != NULL)
            {
                printf("  -> File : %-15s | Count : %d\n",
                       s_temp->file_name, s_temp->word_count);
                s_temp = s_temp->s_sub_link;
            }

            return SUCCESS;
        }
        m_temp = m_temp->main_link;
    }

    // Word not found case
    printf("[ERROR] Word '%s' not found in the database.\n", word);
    return DATA_NOT_FOUND;
}

int get_hash_index(char ch)
{
    // Alphabet characters (a–z)
    if (isalpha(ch))
    {
        return tolower(ch) - 'a';
    }
    // Numeric characters (0–9)
    else if (isdigit(ch))
    {
        return 26;
    }
    // Special characters
    else
    {
        return 27;
    }
}
