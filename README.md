# linux-ls

Rewriting Linux 'ls' command in C.

The following flags are/will be supported:

| Implemented                | flag    | description                                                                                                     |
| -------------------------- | ------- | --------------------------------------------------------------------------------------------------------------- |
| <ul> <li>- [x] </li> </ul> | **-a** | Show hidden entries (a.k.a. files starting with '.')                                                             |
| <ul> <li>- [x] </li> </ul> | **-A** | Do not show current and previous directories ("." and "..")                                                      |
| <ul> <li>- [x] </li> </ul> | **-C** | List entries in tabular format (by columns)                                                                      |
| <ul> <li>- [x] </li> </ul> | **-c** | Sort entries by their "last modification time"                                                                   |
| <ul> <li>- [ ] </li> </ul> | **-d** | List directories themselves, not their contents                                                                  |
| <ul> <li>- [x] </li> </ul> | **-f** | List all files in their order in the directory, without any colors                                               |
| <ul> <li>- [x] </li> </ul> | **-F** | Append indicator (kind of like extension) to the end of the filename, depending on their type (one of */=>@ \| ) |
| <ul> <li>- [x] </li> </ul> | **-g** | Same as `-l`, but do not show owner.                                                                             |
| <ul> <li>- [x] </li> </ul> | **-G** | In list view, do not show group                                                                                  |
| <ul> <li>- [ ] </li> </ul> | **-h** | In list view, show file size in human-readable form (2G, 12M, etc.)                                              |
| <ul> <li>- [x] </li> </ul> | **-i** | Print inode (index number) of each file                                                                          |
| <ul> <li>- [x] </li> </ul> | **-l** | Show entities in long list format                                                                                |
| <ul> <li>- [x] </li> </ul> | **-m** | Show list as comma-separated values                                                                              |
| <ul> <li>- [x] </li> </ul> | **-n** | Same as `-l`, but show owner and group ID                                                                        |
| <ul> <li>- [x] </li> </ul> | **-p** | Put '/' at the end of directory names                                                                            |
| <ul> <li>- [x] </li> </ul> | **-Q** | All file names will be inside quotes                                                                             |
| <ul> <li>- [x] </li> </ul> | **-r** | Reverse order for sorting                                                                                        |
| <ul> <li>- [ ] </li> </ul> | **-R** | List all subdirectories recursively.                                                                             |
| <ul> <li>- [x] </li> </ul> | **-S** | Sort file by size, largest first                                                                                 |
| <ul> <li>- [x] </li> </ul> | **-t** | Sort by time, newest first                                                                                       |
| <ul> <li>- [x] </li> </ul> | **-u** | Sort and show access time. Newest first.                                                                         |
| <ul> <li>- [x] </li> </ul> | **-U** | Do not sort, list entries in directory order                                                                     |
| <ul> <li>- [ ] </li> </ul> | **-x** | List entries by lines                                                                                            |
| <ul> <li>- [x] </li> </ul> | **-X** | Sort alphabetically by file extensions                                                                           |
| <ul> <li>- [x] </li> </ul> | **-1** | List one file per line                                                                                           |
