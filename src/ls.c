#include "parser.h"
#include "sort.h"
#include "print.h"
#include "file_data.h"

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/sysmacros.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define NUM_LEN(n) (snprintf(0, 0, "%+d", (n)) - 1)

#define CURR_DIR "."
#define PREV_DIR ".."

int get_window_width()
{
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return w.ws_col;
}

void update_widths(widths_t *widths, file_info *file)
{
    widths->inode_width = max(widths->inode_width, NUM_LEN(file->st_ino));
    widths->nlink_width = max(widths->nlink_width, NUM_LEN(file->st_nlink));
    widths->ownerid_width = max(widths->ownerid_width, NUM_LEN(file->st_uid));
    widths->ownername_width = max(widths->ownername_width, strlen(file->owner_name));
    widths->groupid_width = max(widths->groupid_width, NUM_LEN(file->st_gid));
    widths->groupname_width = max(widths->groupname_width, strlen(file->group_name));

    int size_width = NUM_LEN(file->st_size);
    if (S_ISCHR(file->st_mode) || S_ISBLK(file->st_mode))
        size_width = NUM_LEN(major(file->st_rdev)) + NUM_LEN(minor(file->st_rdev)) + 2; // major, minor

    widths->size_width = max(widths->size_width, size_width);
    widths->total_blocks += (file->st_blocks / 2);
}

int get_file_data_from_dir(char *directory, file_info *files, options_t *options, widths_t *widths)
{
    DIR *dir;            // for reading directory
    struct dirent *file; // struct for getting file data

    chdir(directory);
    dir = opendir(".");
    int i = 0;

    while ((file = readdir(dir)) != NULL)
    {
        if ((!strcmp(file->d_name, CURR_DIR) || !strcmp(file->d_name, PREV_DIR)) && !options->show_curr_prev_dirs)
            continue;

        if (file->d_name[0] == '.' && !options->show_hidden_files)
            continue;

        lstat(file->d_name, (struct stat *)&files[i]);

        strncpy(files[i].name, file->d_name, 256);
        remove_non_alnum_chars(files[i].name, files[i].alphanum_name);
        get_username_from_uid(files[i].st_uid, files[i].owner_name);
        get_groupname_from_gid(files[i].st_gid, files[i].group_name);
        construct_permission_str(files[i].st_mode, files[i].permission);
        get_file_extension(files[i].name, files[i].extension);
        get_color(files[i].permission, files[i].extension, files[i].color);

        files[i].indicator = get_indicator(files[i].permission);
        update_widths(widths, &files[i]);

        ++i;
    }

    closedir(dir);

    return i;
}

int main(int argc, char *argv[])
{

    file_info files[256]; // For now static array

    widths_t widths;
    memset(&widths, 0, sizeof(widths_t)); // initialize all value with 0
    widths.window_width = get_window_width();

    char dir[256] = {0};
    for (int i = 1; i < argc; ++i)
        if (argv[i][0] != '-') // is not argument
            strcpy(dir, argv[i]);

    options_t options;
    init_options(&options);
    parse_flags(argv, argc, &options);

    if (!dir[0])
        dir[0] = '.';

    int num_of_files = get_file_data_from_dir(dir, files, &options, &widths);
    sort(files, num_of_files, &options);

    print_ls(files, num_of_files, &options, &widths);

    return 0;
}
