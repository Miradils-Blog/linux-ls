#ifndef _FILE_DATA_H
#define _FILE_DATA_H

#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

#define COLOR_RESET "\x1b[0m" // reset color settings
#define COLOR_REGULAR COLOR_RESET
#define COLOR_EXECUTABLES "\x1b[1;32m"
#define COLOR_DIRECTORIES "\x1b[1;34m"
#define COLOR_LINK "\x1b[1;36m"
#define COLOR_FIFO "\x1b[40;33m"
#define COLOR_SOCKET "\x1b[1;35m"
#define COLOR_BLK_CHR "\x1b[40;33;1m"
#define COLOR_BROKEN_LINK "\x1b[40;31;1m"
#define COLOR_ARCHIVE "\x1b[1;31m"

typedef struct
{
    struct stat;
    char name[256];
    char permission[11];
    char color[16];
    char extension[256];
    char indicator; // for -F and -p
    char owner_name[256];
    char group_name[256];

} file_info;

void get_username_from_uid(int uid, char *username);
void get_groupname_from_gid(int gid, char *username);
void construct_permission_str(mode_t mode, char *permission);
void get_file_extension(char *file_name, char *extension);
void get_color(char *permission, char *extension, char *color);
char get_indicator(char *permission);

#endif // _FILE_DATA_H
