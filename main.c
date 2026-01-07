/*
Name         : Chittooru Vinay
Project name : Inverted Search
Reg_id       : 25021_367

Description :
------------------------------------------------------------

OVERVIEW :
This project implements an inverted search mechanism that
indexes multiple text files and allows fast word-based
searching across them.

FUNCTIONALITY :
- Create   : Scan input files and build an index.
- Display  : Show indexed data in a structured format.
- Search   : Find which files contain a word and its count.
- Update   : Load data from backup and avoid re-indexing.
- Save     : Store indexed data for later reuse.

USAGE FLOW :
1. Execute program with .txt files as arguments.
2. Create or update the database using the menu.
3. Search words or display indexed results.
4. Save the database before exiting.
------------------------------------------------------------
*/

#include "insearch.h"

int main(int argc, char *argv[])
{
    int option;                     // User menu choice
    f_list *head = NULL;            // Head pointer for file list
    db_state state = DB_EMPTY;      // Current database state
    c_db hash_table[28];            // Hash table for inverted index

    // Initialize hash table buckets
    for (int i = 0; i < 28; i++)
    {
        hash_table[i].key = i;      // Assign bucket index
        hash_table[i].m_link = NULL;// No main nodes initially
    }

    // Validate command-line arguments
    if (argc < 2)
    {
        printf("[ERROR] No input files provided.\n");
        printf("[USAGE] ./invsearch <file1.txt> <file2.txt> ...\n");
        return FAILURE;
    }

    // Read and validate file list
    if (read_and_validate(argc, argv, &head) != SUCCESS)
    {
        printf("[ERROR] File validation failed.\n");
        return FAILURE;
    }

    // Menu-driven program loop
    while (1)
    {
        // Display available operations
        printf("\n=========== MENU ===========\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Search Database\n");
        printf("4. Update Database\n");
        printf("5. Save Database\n");
        printf("6. Exit\n");
        printf("============================\n");
        printf("Enter your choice : ");

        if (scanf("%d", &option) != 1)
            option = 0;

        switch (option)
        {
            case 1:
                // Create database from file list
                if (state == DB_EMPTY || state == DB_UPDATED)
                {
                    if (create_database(head, hash_table) == SUCCESS)
                    {
                        state = DB_CREATED;
                        printf("[SUCCESS] Database created successfully.\n");
                    }
                }
                else
                {
                    printf("[WARNING] Database already exists.\n");
                }
                break;

            case 2:
                // Display database contents
                if (state != DB_EMPTY)
                {
                    display_database(hash_table);
                }
                else
                {
                    printf("[INFO] Database is empty. Create it first.\n");
                }
                break;

            case 3:
                // Search for a specific word
                if (state != DB_EMPTY)
                {
                    char word[30];
                    printf("Enter word to search : ");
                    scanf("%s", word);
                    search_database(hash_table, word);
                }
                else
                {
                    printf("[ERROR] Database not created yet.\n");
                }
                break;

            case 4:
                // Update database using backup
                if (state == DB_EMPTY)
                {
                    if (update_database(hash_table, &head) == SUCCESS)
                    {
                        state = DB_UPDATED;
                        printf("[SUCCESS] Database updated from backup.\n");
                    }
                }
                else
                {
                    printf("[ERROR] Update allowed only before creation.\n");
                }
                break;

            case 5:
                // Save database to file
                if (save_database(hash_table) == SUCCESS)
                {
                    printf("[SUCCESS] Database saved successfully.\n");
                }
                else
                {
                    printf("[ERROR] Failed to save database.\n");
                }
                break;

            case 6:
                // Exit program
                printf("[INFO] Exiting program. Goodbye!\n");
                return SUCCESS;

            default:
                printf("[ERROR] Invalid choice. Try again.\n");
        }

        getchar(); // Clear input buffer
    }

    return SUCCESS;
}
