#ifndef _LS_H
#define _LS_H

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define NUM_LEN(n) (snprintf(0, 0, "%+d", (n)) - 1)

typedef struct
{
    int window_width;
    int inode_width;
    int nlink_width;
    int ownername_width;
    int ownerid_width;
    int groupname_width;
    int groupid_width;
    int block_width;
    int size_width;
    int total_blocks;
} widths_t;

#endif // _LS_H
