#include "inverted_search.h"

int create_database(Flist *fhead, Mlist *htable[])
{
    static int created = 0;

    if (created)
    {
        printf("INFO : Database already created\n");
        return FAILURE;
    }

    if (index_new_files(fhead, htable))
    {
        created = 1;
        printf("INFO : Database created successfully\n");
        return SUCCESS;
    }

    printf("INFO : No data to create database\n");
    return FAILURE;
}
