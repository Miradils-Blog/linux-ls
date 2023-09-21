#include "ls.h"
#include <stdio.h>
#include <dirent.h>
#include <parser.h>
#include <file_data.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/sysmacros.h>

int get_window_width()
{
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return w.ws_col;
}

void update_widths(widths_t *widths, file_info *file)
{
    widths->inode_width = max(widths->inode_width, NUM_LEN(file->st_ino));
    widths->block_width = max(widths->block_width, NUM_LEN(file->st_size));
    widths->nlink_width = max(widths->inode_width, NUM_LEN(file->st_nlink));
    widths->ownerid_width = max(widths->ownerid_width, NUM_LEN(file->st_uid));
    widths->ownername_width = max(widths->ownername_width, strlen(file->owner_name));
    widths->groupid_width = max(widths->groupid_width, NUM_LEN(file->st_gid));
    widths->groupname_width = max(widths->groupname_width, strlen(file->group_name));

    int size_width = NUM_LEN(file->st_size);
    if (S_ISCHR(file->st_mode) || S_ISBLK(file->st_mode))
        size_width = NUM_LEN(major(file->st_rdev)) + NUM_LEN(minor(file->st_rdev)) + 2; // major, minor

    widths->size_width = max(widths->size_width, size_width);
    widths->total_blocks += file->st_blocks;
}

int get_file_data_from_dir(char *directory, file_info *files, widths_t *widths)
{
    DIR *dir;            // for reading directory
    struct dirent *file; // struct for getting file data

    chdir(directory);
    dir = opendir(".");
    int i = 0;

    while ((file = readdir(dir)) != NULL)
    {
        stat(file->d_name, (struct stat *)&files[i]);

        strncpy(files[i].name, file->d_name, 256);
        get_username_from_uid(files[i].st_uid, files[i].owner_name);
        get_groupname_from_gid(files[i].st_gid, files[i].group_name);
        construct_permission_str(files[i].st_mode, files[i].permission);
        get_file_extension(files[i].name, files[i].extension);
        get_color(files[i].permission, files[i].extension, files[i].color);

        files[i].indicator = get_indicator(files[i].permission);
        update_widths(widths, &files[i]);

        ++i;
    }

    return i;
}

int main(int argc, char *argv[])
{

    file_info files[256]; // For now static array

    widths_t widths;
    memset(&widths, 0, sizeof(widths_t)); // initialize all value with 0
    widths.window_width = get_window_width();

    int num_of_files = get_file_data_from_dir("folder", files, &widths);

    char filetime[20];
    struct tm *timeinfo;

    for (int j = 0; j < num_of_files; ++j)
    {
        timeinfo = localtime(&files[j].st_mtime);
        strftime(filetime, 20, "%b %-2d %H:%M", timeinfo);

        printf("%9d %5d %s %d %-8s %-7s %8d %s %s%s%s\n", files[j].st_ino, files[j].st_blocks / 2, files[j].permission, files[j].st_nlink,
               files[j].owner_name, files[j].group_name, files[j].st_size, filetime, files[j].color, files[j].name, COLOR_RESET);
    }

    return 0;
}
