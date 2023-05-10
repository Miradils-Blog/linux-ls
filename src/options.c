#include <options.h>
#include <stdio.h>

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
                case 'c':
                    options->sort_by = BY_MODIFICATION_TIME;
                    break;
                case 'C':
                    options->print_style = TABULAR_FORMAT;
                    break;
                case 'f':
                    options->sort_by = NO_SORT;
                    break;
                case 'g':
                    options->print_style = LIST_FORMAT;
                    break;
                case 'l':
                    options->print_style = LIST_FORMAT;
                    break;
                case 'n':
                    options->print_style = LIST_FORMAT;
                    break;
                case 'm':
                    options->print_style = COMMA_SEPARATED_FORMAT;
                    break;
                case 'r':
                    options->reverse_sort = true;
                    break;
                case 'S':
                    options->sort_by = BY_SIZE;
                    break;
                case 't':
                    options->sort_by = BY_CREATION_TIME;
                    break;
                case 'u':
                    options->sort_by = BY_ACCESS_TIME;
                    break;
                case 'U':
                    options->sort_by = NO_SORT;
                    break;
                case 'x':
                    options->print_style = ONE_LINE_FORMAT;
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
}
