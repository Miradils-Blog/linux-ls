#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char command[50] = "ls ";

    for (int i = 1; i < argc; ++i)
    {
        strcat(command, argv[i]);
        strcat(command, " ");
    }

    system(command);
    return 0;
}
