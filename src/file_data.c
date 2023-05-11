#include <file_data.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

void get_username_from_uid(int uid, char *username)
{
    struct passwd *pws;
    pws = getpwuid(uid);

    strncpy(username, 256, pws->pw_name);
}

void get_groupname_from_gid(int gid, char *groupname)
{
    struct group *grp;
    grp = getgrgid(gid);

    strncpy(groupname, 256, grp->gr_name);
}

void construct_permission_str(mode_t mode, char *permission)
{
    // Get the first character from file type
    if      (S_ISREG(mode)) permission[0] = '-';
    else if (S_ISDIR(mode)) permission[0] = 'd';
    else if (S_ISLNK(mode)) permission[0] = 'l';
    else if (S_ISCHR(mode)) permission[0] = 'c';
    else if (S_ISBLK(mode)) permission[0] = 'b';
    else if (S_ISSOCK(mode)) permission[0] = 's';
    else if (S_ISFIFO(mode)) permission[0] = 'p';

    permission[1] = (mode & S_IRUSR) ? 'r' : '-';
    permission[2] = (mode & S_IWUSR) ? 'w' : '-';
    permission[3] = (mode & S_IXUSR) ? 'x' : '-';
    
    permission[4] = (mode & S_IRGRP) ? 'r' : '-';
    permission[5] = (mode & S_IWGRP) ? 'w' : '-';
    permission[6] = (mode & S_IXGRP) ? 'x' : '-';

    permission[7] = (mode & S_IROTH) ? 'r' : '-';
    permission[8] = (mode & S_IWOTH) ? 'w' : '-';
    permission[9] = (mode & S_IXOTH) ? 'x' : '-';
    permission[10] = 0;  // terminator char, just in case
}

void get_file_extension(char *file_name, char *extension)
{
    char *p = strrchr(file_name, '.');
    
    if (p)
        strcpy(extension, strrchr(file_name, '.'));
}

static bool is_archive_file(char *extension)
{
    return (strstr(extension, ".tar") || strstr(extension, ".taz") || strstr(extension, ".xz") || strstr(extension, ".gz"));
}

void get_color(char* permission, char *extension, char *color)
{
    switch (permission[0])
    {
    case '-':
        if (permission[3] == 'x' || permission[6] == 'x' || permission[9] == 'x')
            strcpy(color, COLOR_EXECUTABLES);
        else if (is_archive_file(extension))
            strcpy(color, COLOR_ARCHIVE);
        else
            strcpy(color, COLOR_REGULAR);
        break;
    case 'd':
        strcpy(color, COLOR_DIRECTORIES);
        break;
    case 'l':
        strcpy(color, COLOR_LINK);
        break;
    case 'c':
    case 'b':
        strcpy(color, COLOR_BLK_CHR);
        break;
    case 's':
        strcpy(color, COLOR_SOCKET);
        break;
    case 'p':
        strcpy(color, COLOR_FIFO);
        break;
    default:
        break;
    }
}


char get_indicator(char* permission)
{
    switch (permission[0])
    {
    case '-':
        if (permission[3] == 'x' || permission[6] == 'x' || permission[9] == 'x')
            return '*';
        
        return ' '; 
    case 'd':
        return '/';
    case 'l':
        return '@';
    case 's':
        return '=';
    case 'p':
        return '|';
    default:
        return ' ';
    }
}
