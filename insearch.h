#ifndef INSEARCH
#define INSEARCH

// Standard header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Macro definitions for function return status
#define SUCCESS 1
#define FAILURE -1
#define DATA_NOT_FOUND 2

// Enum to track database state
typedef enum
{
    DB_EMPTY,     // Database not created
    DB_CREATED,   // Database created from input files
    DB_UPDATED    // Database updated from backup
} db_state;

// Linked list to store input file names
typedef struct file_node
{
    char f_name[30];              // File name
    struct file_node *link;       // Pointer to next file
} f_list;

// Main node structure (one per unique word)
typedef struct main_node
{
    int file_count;               // Number of files containing the word
    char word[30];                // Indexed word
    struct main_node *main_link;  // Next word node
    struct sub_node *sub_link;    // Pointer to sub-node list
} m_node;

// Sub node structure (file-wise word count)
typedef struct sub_node
{
    int word_count;               // Number of occurrences in a file
    char file_name[30];           // File name
    struct sub_node *s_sub_link;  // Next sub-node
} s_node;

// Hash table structure
typedef struct create_database
{
    int key;                      // Hash index
    m_node *m_link;               // Pointer to main node list
} c_db;

// Function prototypes
int read_and_validate(int argc, char *argv[], f_list **head);
int open_files(char *argv);
int create_database(f_list *head, c_db *arr);
int display_database(c_db *hash_t);
int search_database(c_db *hash_table, char *word);
int update_database(c_db *hash_t, f_list **head);
int save_database(c_db *hash_t);
int get_hash_index(char ch);

#endif
