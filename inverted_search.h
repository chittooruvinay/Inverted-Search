#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 26
#define SUCCESS 0
#define FAILURE -1

typedef struct file_node
{
    char file_name[50];
    int indexed;                 // 1 = committed to DB, 0 = pending
    struct file_node *next;
} Flist;

typedef struct sub_node
{
    char file_name[50];
    int word_count;
    struct sub_node *next;
} Slist;

typedef struct main_node
{
    char word[50];
    int file_count;
    struct main_node *next;
    Slist *slink;
} Mlist;

/* functions */
int insert_file(Flist **, char *);
int load_database(char *, Mlist *[], Flist **);
int index_new_files(Flist *, Mlist *[]);
int create_database(Flist *, Mlist *[]);
int update_database(Mlist *[], Flist *);
void display_database(Mlist *[]);
int search_database(Mlist *[], char *);
int save_database(Mlist *[], char *);

#endif
