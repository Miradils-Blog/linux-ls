#ifndef _PARSER_H
#define _PARSER_H

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
    MODIFICATION_TIMESTAMP,  // mtime
    CHANGE_TIMESTAMP,        // ctime
    ACCESS_TIMESTAMP         // atime
} time_attribute_t;

typedef struct
{
    bool show_extra_data;  // -l, -g, -n
    bool show_owner_ids;  // -n
    bool show_owner;  // -g
    bool show_owner_group;  // -G
    bool show_readable_size; // -h
    time_attribute_t show_timestamp;
    
} long_list_settings_t;


typedef enum
{
    BY_ALPHABETICAL,          // (default)
    NO_SORT,                  // -f, -U
    BY_MODIFICATION_TIME,     // -t
    BY_CHANGE_TIME,           // -c
    BY_ACCESS_TIME,           // -u
    BY_SIZE,                  // -S
    BY_ALPHABETICAL_EXTENSION // -X
} sort_option_t;

typedef struct
{
    print_style_t print_style;
    long_list_settings_t ll_settings;
    
    bool show_hidden_files;
    bool show_curr_prev_dirs;
    
    bool colorful_output;
    bool show_directory_content;
    
    bool append_file_indicators;
    bool append_directory_indicator;
    
    bool show_inode;
    bool inside_quotes;
    bool recursive;

    sort_option_t sort_by;
    bool reverse_sort;
} options_t;

// Function Prototypes
void parse_flags(char *flags[], int count, options_t *options);

#endif // _PARSER_H
