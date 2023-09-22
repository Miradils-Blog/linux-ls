#include "print.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

static void print_name(file_info file, options_t *options)
{
    if (options->colorful_output)
        printf("%s", file.color);

    if (options->inside_quotes)
        printf("\"");

    printf("%s", file.name);

    if (options->inside_quotes)
        printf("\"");

    if (options->append_file_indicators)
        printf("%c", file.indicator);
    else if (options->append_directory_indicator && file.permission[0] == 'd')
        printf("%c", file.indicator);

    if (options->colorful_output)
        printf("%s", COLOR_RESET);
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

            printf("%*d ", widths->size_width, files[i].st_size);

            char filetime[14];
            struct tm *timeinfo;

            if (options->sort_by == ACCESS_TIMESTAMP)
                timeinfo = localtime(&files[i].st_atime);
            else if (options->sort_by == CHANGE_TIMESTAMP)
                timeinfo = localtime(&files[i].st_ctime);
            else
                timeinfo = localtime(&files[i].st_mtime);

            // For files which was accessd/modified was a looong time ago, format is ("%b %e  %Y")

            strftime(filetime, 15, "%b %e %H:%M ", timeinfo);
            printf("%13s", filetime);
        }

        print_name(files[i], options);

        if (files[i].permission[0] == 'l')
        {
            printf(" -> ");

            int len;
            char buff[256];
            file_info linked_file;

            len = readlink(files[i].name, buff, sizeof(buff));
            buff[len] = 0;
            // printf("NAME IS:%s", buff);
            strncpy(linked_file.name, buff, len);

            stat(files[i].name, (struct stat *)&linked_file);
            construct_permission_str(linked_file.st_mode, linked_file.permission);
            get_color(linked_file.permission, linked_file.extension, linked_file.color);

            // printf("%s %s", linked_file.permission, linked_file.color);

            print_name(linked_file, options);
        }

        printf("\n");
    }
}

static void print_comma_sep(file_info *files, int count, options_t *options, widths_t *widths)
{
    if (count)
        print_name(files[0], options);

    for (int i = 1; i < count; ++i)
    {
        printf(", ");
        print_name(files[i], options);
    }

    printf("\n");
}

static void print_tabular(file_info *files, int count, options_t *options, widths_t *widths)
{
}

void print_ls(file_info *files, int count, options_t *options, widths_t *widths)
{
    if (options->print_style == LIST_FORMAT)
        print_list(files, count, options, widths);
    else if (options->print_style == COMMA_SEPARATED_FORMAT)
        print_comma_sep(files, count, options, widths);
    else
        print_tabular(files, count, options, widths);
}
