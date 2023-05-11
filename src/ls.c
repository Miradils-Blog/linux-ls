#include <stdio.h>
#include <dirent.h>
#include <options.h>
#include <file_data.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{

    DIR *dir;            // for reading directory
    struct dirent *file; // struct for getting file data
    file_info files[256];  // For now static array

    chdir("folder");
    dir = opendir(".");
    int i = 0;

    while ((file = readdir(dir)) != NULL)
    {
        lstat(file->d_name, (struct stat *)&files[i]);

        strncpy(files[i].name, 256, file->d_name);
        get_username_from_uid(files[i].st_uid, files[i].owner_name);
        get_groupname_from_gid(files[i].st_gid, files[i].group_name);
        construct_permission_str(files[i].st_mode, files[i].permission);
        get_file_extension(files[i].name, files[i].extension);
        get_color(files[i].permission, files[i].extension, files[i].color);
        
        files[i].indicator = get_indicator(files[i].permission);
        ++i;
    }

    char filetime[20];
    struct tm * timeinfo;

    for (int j = 0; j < i; ++j)
    {
        timeinfo = localtime(&files[j].st_mtime);
        strftime(filetime, 20, "%b %-2d %H:%M", timeinfo);

        printf("%9d %5d %s %d %-8s %-7s %8d %s %s%s%s\n", files[j].st_ino, files[j].st_blocks / 2, files[j].permission, files[j].st_nlink, 
                                                    files[j].owner_name, files[j].group_name, files[j].st_size, filetime, files[j].color, files[j].name, COLOR_RESET);
    }

    return 0;
}
