#ifndef _OPTIONS_H
#define _OPTIONS_H

#include <stdbool.h>

typedef enum
{
    TABULAR_FORMAT,         // -C (default)
    LIST_FORMAT,            // -l, -1
    COMMA_SEPARATED_FORMAT, // -m
    ONE_LINE_FORMAT,        // -x

} print_style_t;

typedef enum
{
    BY_ALPHABETICAL,          // (default)
    NO_SORT,                  // -f, -U
    BY_MODIFICATION_TIME,     // -c
    BY_SIZE,                  // -S
    BY_CREATION_TIME,         // -t
    BY_ACCESS_TIME,           // -u
    BY_ALPHABETICAL_EXTENSION // -X
} sort_option_t;

typedef struct
{
    print_style_t print_style;
    bool show_hidden_files;
    bool show_curr_prev_dirs;
    sort_option_t sort_by;
    bool reverse_sort;
} options_t;

/////////////////////////////////////////////////////////
////////////////// Function Prototypes //////////////////
/////////////////////////////////////////////////////////

void parse_flags(char *flags[], int count, options_t *options);

#endif // _OPTIONS_H
