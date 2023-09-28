#include "sort.h"

#include <stdlib.h>
#include <string.h>
#include <strings.h>

static int cmp_alphabetical_asc(const void *a, const void *b)
{
    char *name1 = ((file_info *)a)->alphanum_name;
    char *name2 = ((file_info *)b)->alphanum_name;

    int len_cmp = strlen(((file_info *)a)->name) - strlen(((file_info *)b)->name);
    if (strlen(name1) || strlen(name2))
        len_cmp = -len_cmp;

    return strcasecmp(name1, name2) ?: len_cmp;
}

static int cmp_alphabetical_desc(const void *a, const void *b) { return -cmp_alphabetical_asc(a, b); }

static int cmp_alphabetical_ext_asc(const void *a, const void *b)
{
    return strcasecmp(((file_info *)a)->extension, ((file_info *)b)->extension);
}
static int cmp_alphabetical_ext_desc(const void *a, const void *b) { return -cmp_alphabetical_ext_asc(a, b); }

static int cmp_atime_desc(const void *a, const void *b)
{
    return (((file_info *)b)->st_atime - ((file_info *)a)->st_atime) ?: cmp_alphabetical_asc(a, b);
}
static int cmp_atime_asc(const void *a, const void *b) { return -cmp_atime_asc(a, b); }

static int cmp_ctime_desc(const void *a, const void *b)
{
    return (((file_info *)b)->st_ctime - ((file_info *)a)->st_ctime) ?: cmp_alphabetical_asc(a, b);
}
static int cmp_ctime_asc(const void *a, const void *b) { return -cmp_ctime_asc(a, b); }

static int cmp_mtime_desc(const void *a, const void *b)
{
    return (((file_info *)b)->st_mtime - ((file_info *)a)->st_mtime) ?: cmp_alphabetical_asc(a, b);
}
static int cmp_mtime_asc(const void *a, const void *b) { return -cmp_mtime_asc(a, b); }

static int cmp_size_asc(const void *a, const void *b)
{
    return ((file_info *)a)->st_size - ((file_info *)b)->st_size;
}
static int cmp_size_desc(const void *a, const void *b) { return -cmp_size_asc(a, b); }

void sort(file_info *files, int count, options_t *options)
{
    int (*cmp_func)(const void *, const void *);

    switch (options->sort_by)
    {
    case BY_ALPHABETICAL:
        cmp_func = (!options->reverse_sort) ? cmp_alphabetical_asc : cmp_alphabetical_desc;
        break;
    case BY_ALPHABETICAL_EXTENSION:
        cmp_func = (!options->reverse_sort) ? cmp_alphabetical_ext_asc : cmp_alphabetical_ext_desc;
        break;
    case BY_ACCESS_TIME:
        cmp_func = (!options->reverse_sort) ? cmp_atime_desc : cmp_atime_asc;
        break;
    case BY_CHANGE_TIME:
        cmp_func = (!options->reverse_sort) ? cmp_ctime_desc : cmp_ctime_asc;
        break;
    case BY_MODIFICATION_TIME:
        cmp_func = (!options->reverse_sort) ? cmp_mtime_desc : cmp_mtime_asc;
        break;
    case BY_SIZE:
        cmp_func = (!options->reverse_sort) ? cmp_size_asc : cmp_size_desc;
        break;
    default:
        return;
    }

    qsort(files, count, sizeof(file_info), cmp_func);
}
