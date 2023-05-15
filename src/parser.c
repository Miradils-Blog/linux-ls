#include <parser.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void init_options(options_t *options)
{
    memset(options, 0, sizeof(*options));  // Initialize all values to zero

    options->ll_settings.show_owner = true;
    options->ll_settings.show_owner_group = true;
    options->colorful_output = true;
    options->show_directory_content = true;
}

void parse_flags(char *flags[], int count, options_t *options)
{
    for (int i = 0; i < count; ++i)
    {
        if (flags[i][0] == '-') // it is a flag
        {
            while (*(++flags[i])) // iterate through characters/flags
            {
                switch (*flags[i])
                {
                case 'a':
                    options->show_hidden_files = true;
                    options->show_curr_prev_dirs = true;
                    break;
                case 'A':
                    options->show_hidden_files = true;
                    options->show_curr_prev_dirs = false;
                    break;
                case 'c':
                    options->ll_settings.show_timestamp = CHANGE_TIMESTAMP;
                    break;
                case 'C':
                    options->print_style = TABULAR_FORMAT;
                    break;
                case 'd':
                    options->show_directory_content = false;
                    break;
                case 'f':
                    options->print_style = TABULAR_FORMAT;
                    options->sort_by = NO_SORT;
                    options->show_hidden_files = true;
                    options->show_curr_prev_dirs = true;
                    options->colorful_output = false;
                    break;
                case 'F':
                    options->append_file_indicators = true;
                    options->append_directory_indicator = true;
                    break;
                case 'g':
                    options->ll_settings.show_owner = false;
                    options->ll_settings.show_extra_data = true;
                    options->print_style = LIST_FORMAT;
                    break;
                case 'G':
                    options->ll_settings.show_owner_group = false;
                    break;
                case 'h':
                    options->ll_settings.show_readable_size = true;
                    break;
                case 'i':
                    options->show_inode = true;
                    break;
                case 'l':
                    options->ll_settings.show_extra_data = true;
                    options->print_style = LIST_FORMAT;
                    break;
                case 'm':
                    options->print_style = COMMA_SEPARATED_FORMAT;
                    break;
                case 'n':
                    options->ll_settings.show_owner_ids = true;
                    options->ll_settings.show_extra_data = true;
                    options->print_style = LIST_FORMAT;
                    break;
                case 'p':
                    options->append_directory_indicator = true;
                    break;
                case 'Q':
                    options->inside_quotes = true;
                    break;
                case 'r':
                    options->reverse_sort = true;
                    break;
                case 'R':
                    options->recursive = true;
                    break;
                case 'S':
                    options->sort_by = BY_SIZE;
                    break;
                case 't':
                    options->sort_by = BY_MODIFICATION_TIME;
                    break;
                case 'u':
                    options->ll_settings.show_timestamp = ACCESS_TIMESTAMP;
                    break;
                case 'U':
                    options->sort_by = NO_SORT;
                    break;
                case 'x':
                    options->print_style = ONE_LINE_FORMAT;
                    break;
                case 'X':
                    options->sort_by = BY_ALPHABETICAL_EXTENSION;
                    break;
                case '1':
                    options->print_style = LIST_FORMAT;
                    break;
                default:
                    break;  
                }
            }
        }
    }

    // If active sort option is BY_MODIFICATION_TIME, meaning -t 
    // is set, check if -u or -c is also set, and change sorting accordingly.
    if (options->sort_by == BY_MODIFICATION_TIME)
        // Little hack: The orders in enums are the same, so we can use math
        options->sort_by += options->ll_settings.show_timestamp;
    else if (options->print_style != LIST_FORMAT && !options->sort_by && !options->ll_settings.show_timestamp)
        // In non-list view, if show timestamp is not MODIFICATION_TIMESTAMP, it means
        // -u or -c is set, so, if there is no other sort option, they become our sort option
        options->sort_by = BY_MODIFICATION_TIME + options->ll_settings.show_timestamp;
}
