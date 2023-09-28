#include "print.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <string.h>

typedef struct
{
    int valid;
    int line_len;
    int max_len[256]; // Max possible length for each col
} column_info;

#define MIN_COLUMN_WIDTH 3 // 1 char + 2 spaces

static void print_padded_name(file_info file, options_t *options, int pad)
{
    static bool reset_color = true;

    // Consider colors, quotes and indicator
    char *filename = calloc(strlen(file.name) + 20, sizeof(char));
    int len = 0;
    int full_pad = pad;

    // Do not print, if there is no color
    if (options->colorful_output && strcmp(file.color, COLOR_REGULAR))
    {
        // if there is colorful output, reset color in the beginning, only once
        if (reset_color)
        {
            len += sprintf(filename + len, "%s", COLOR_RESET);
            reset_color = false;
            full_pad += strlen(COLOR_RESET);
        }

        len += sprintf(filename + len, "%s", file.color);
        full_pad += strlen(file.color);
    }

    if (options->inside_quotes)
        filename[len++] = '\"';

    len += sprintf(filename + len, "%s", file.name);

    if (options->inside_quotes)
        filename[len++] = '\"';

    // Do not print, if there is no color
    if (options->colorful_output && strcmp(file.color, COLOR_REGULAR))
    {
        len += sprintf(filename + len, "%s", COLOR_RESET);
        full_pad += strlen(COLOR_RESET);
    }

    // Indicator is without color
    if (options->append_file_indicators && file.indicator)
        filename[len++] = file.indicator;
    else if (options->append_directory_indicator && file.permission[0] == 'd' && file.indicator)
        filename[len++] = file.indicator;

    printf("%-*s", full_pad, filename);
}

static void print_name(file_info file, options_t *options)
{
    print_padded_name(file, options, 0);
}

static void print_list(file_info *files, int count, options_t *options, widths_t *widths)
{
    if (options->show_total)
        printf("total %d\n", widths->total_blocks);

    for (int i = 0; i < count; ++i)
    {

        if (options->show_inode)
            printf("%*d ", widths->inode_width, files[i].st_ino);

        if (options->ll_settings.show_extra_data)
        {
            printf("%s ", files[i].permission);
            printf("%*d ", widths->nlink_width, files[i].st_nlink);

            if (options->ll_settings.show_owner)
            {
                if (options->ll_settings.show_owner_ids)
                    printf("%*d ", widths->ownerid_width, files[i].st_uid);
                else
                    printf("%-*s ", widths->ownername_width, files[i].owner_name);
            }

            if (options->ll_settings.show_owner_group)
            {
                if (options->ll_settings.show_owner_ids)
                    printf("%*d ", widths->groupid_width, files[i].st_gid);
                else
                    printf("%-*s ", widths->groupname_width, files[i].group_name);
            }

            if (S_ISCHR(files[i].st_mode) || S_ISBLK(files[i].st_mode))
            {
                char devices[10];
                sprintf(devices, "%d, %d", major(files[i].st_rdev), minor(files[i].st_rdev));
                printf("%*s ", widths->size_width, devices);
            }
            else
                printf("%*d ", widths->size_width, files[i].st_size);

            char filetime[14];
            struct tm *timeinfo;

            if (options->ll_settings.show_timestamp == ACCESS_TIMESTAMP)
                timeinfo = localtime(&files[i].st_atime);
            else if (options->ll_settings.show_timestamp == CHANGE_TIMESTAMP)
                timeinfo = localtime(&files[i].st_ctime);
            else
                timeinfo = localtime(&files[i].st_mtime);

            // For files which was accessd/modified was a looong time ago, format is ("%b %e  %Y")

            strftime(filetime, 15, "%b %e %H:%M ", timeinfo);
            printf("%13s", filetime);
        }

        print_name(files[i], options);

        if (options->ll_settings.show_extra_data && files[i].permission[0] == 'l')
        {
            printf(" -> ");

            int len;
            char buff[256];
            file_info linked_file;

            len = readlink(files[i].name, buff, sizeof(buff));
            strncpy(linked_file.name, buff, len);
            linked_file.name[len] = 0;

            stat(files[i].name, (struct stat *)&linked_file);
            construct_permission_str(linked_file.st_mode, linked_file.permission);
            get_color(linked_file.permission, linked_file.extension, linked_file.color);
            linked_file.indicator = get_indicator(linked_file.permission);

            print_name(linked_file, options);
        }

        printf("\n");
    }
}

static void print_comma_sep(file_info *files, int count, options_t *options, widths_t *widths)
{
    print_name(files[0], options);

    for (int i = 1; i < count; ++i)
    {
        printf(", ");
        print_name(files[i], options);
    }

    printf("\n");
}

static int get_column_count(column_info *column_configs, file_info *files, int file_count, widths_t *widths, options_t *options)
{
    int max_idx = widths->window_width / MIN_COLUMN_WIDTH - 1;
    int max_cols = (max_idx < file_count) ? max_idx : file_count;
    int inode = (options->show_inode) ? widths->inode_width : 0;

    for (int file_idx = 0; file_idx < file_count; ++file_idx)
    {
        for (int config_idx = 0; config_idx < max_cols; ++config_idx)
        {
            if (!column_configs[config_idx].valid)
                continue; // Skip invalid configurations

            int rows = (file_count + config_idx) / (config_idx + 1);

            // If too much allocated column/row space
            if ((rows * (config_idx + 1) - file_count) > rows)
            {
                column_configs[config_idx].valid = 0;
                continue;
            }

            // find file column
            int col = file_idx / rows;

            int name_width = strlen(files[file_idx].name);

            if (options->inside_quotes)
                name_width += 2;

            if (options->append_file_indicators && files[file_idx].indicator)
                name_width += 1;
            else if (options->append_file_indicators && files[file_idx].permission[0] == 'd')
                name_width += 1;

            // Check if the file name width exceeds the current column width
            if (name_width > column_configs[config_idx].max_len[col])
            {
                column_configs[config_idx].line_len += name_width - column_configs[config_idx].max_len[col];
                column_configs[config_idx].max_len[col] = name_width;
            }

            // Consider spaces as well
            if (column_configs[config_idx].line_len + (2 * config_idx) + (inode * (config_idx + 1)) > widths->window_width)
                column_configs[config_idx].valid = 0;
        }
    }

    // Find the highest valid configuration
    int selected_config = max_cols - 1;
    while (selected_config >= 0 && (!column_configs[selected_config].valid || !column_configs[selected_config].max_len[selected_config]))
        selected_config--;

    return selected_config + 1; // Return the number of columns
}

static void
print_tabular(file_info *files, int file_count, options_t *options, widths_t *widths)
{
    column_info column_configs[256] = {[0 ... 255] = {1, 0, 0, 0}};

    int ncols = get_column_count(column_configs, files, file_count, widths, options);
    int nrows = (file_count + ncols - 1) / ncols;

    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            int file_idx = i + j * nrows;

            if (options->show_inode)
                printf("%*d ", widths->inode_width, files[file_idx].st_ino);

            print_padded_name(files[file_idx], options, column_configs[ncols - 1].max_len[j]);
            if (j < ncols - 1)
                printf("  ");
        }
        printf("\n");
    }
}

void print_ls(file_info *files, int count, options_t *options, widths_t *widths)
{
    if (!count)
        return;

    if (options->print_style == LIST_FORMAT)
        print_list(files, count, options, widths);
    else if (options->print_style == COMMA_SEPARATED_FORMAT)
        print_comma_sep(files, count, options, widths);
    else
        print_tabular(files, count, options, widths);
}
